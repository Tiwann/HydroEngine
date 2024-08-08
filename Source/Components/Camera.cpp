#include "HydroPCH.h"
#include "Camera.h"
#include "Math/LinearAlgebra.h"
#include "Transform.h"
#include "Core/Application.h"
#include "Core/GameObject.h"
#include "Core/Window.h"

namespace Hydro
{
    Camera::Camera(GameObject* Owner) : Component(Owner, "Camera")
    {                             
    }

    void Camera::OnUpdate(float Delta)
    {
        const Application& App = Application::GetCurrentApplication();
        const Ref<Window>& Window = App.GetWindow();
        
        Settings.Width = Window->GetWidth();
        Settings.Height = Window->GetHeight();
    }

    void Camera::OnInspectorGUI(const ImGuiIO& IO)
    {
        Component::OnInspectorGUI(IO);
        
        ImGui::DragFloat("Width", &Settings.Width);
        ImGui::DragFloat("Height", &Settings.Height);
        ImGui::DragFloat("Near Plane", &Settings.NearPlane);
        ImGui::DragFloat("Far Plane", &Settings.FarPlane);

        const char* ProjectionTypes[2] = { "Perspective", "Orthographic" };
        ImGui::Combo("Projection", (int*)&Settings.Projection, ProjectionTypes, 2);
            
        if(Settings.Projection == CameraProjectionType::Orthographic)
        {
            ImGui::DragFloat("Orthographic Size", &Settings.OrthoSize);
        } else
        {
            ImGui::DragFloat("Field Of View", &Settings.FieldOfView);
        }
    }

    Matrix4 Camera::GetViewMatrix() const
    {
        return m_GameObject->GetTransform()->GetWorldSpaceMatrix().Inverse();
    }

    Matrix4 Camera::GetProjectionMatrix() const
    {
        const float AspectRatio = Settings.Width / Settings.Height;
        
        const Matrix4 PerspectiveProj = Math::Perspective(
            Settings.FieldOfView,
            AspectRatio,
            Settings.NearPlane,
            Settings.FarPlane);

        const Matrix4 OrthoProj = Math::Orthographic(
            Settings.Width,
            Settings.Height,
            Settings.OrthoSize,
            Settings.NearPlane,
            Settings.FarPlane);
        
        const Matrix4 Projection = Settings.Projection == CameraProjectionType::Perspective ? PerspectiveProj : OrthoProj;
          
        return Projection;
    }
}

