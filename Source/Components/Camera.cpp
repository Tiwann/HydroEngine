#include "Camera.h"
#include "Math/LinearAlgebra.h"
#include "Transform.h"
#include "Core/Application.h"
#include "Core/Entity.h"
#include "Core/Window.h"
#include "Editor/EditorGUI.h"

namespace Hydro
{
    Camera::Camera(Entity* Owner) : Component(Owner, "Camera")
    {                             
    }

    void Camera::OnUpdate(float Delta)
    {
        const Application& App = *g_Application;
        const Ref<Window>& Window = App.GetWindow();
        
        Settings.Width = Window->GetWidth();
        Settings.Height = Window->GetHeight();
    }

    void Camera::OnInspectorGUI(const ImGuiIO& IO)
    {
        Component::OnInspectorGUI(IO);
        
        UI::DragValue<float>("Width", Settings.Width, 1, 0, 0, "%.0f");
        UI::DragValue<float>("Height", Settings.Height, 1, 0, 0, "%.0f");
        UI::DragValue<float>("Near Plane", Settings.NearPlane);
        UI::DragValue<float>("Far Plane", Settings.FarPlane);

        const char* ProjectionTypes[2] = { "Perspective", "Orthographic" };
        ImGui::Combo("Projection", (int*)&Settings.Projection, ProjectionTypes, 2);
            
        if(Settings.Projection == CameraProjectionType::Orthographic)
        {
            UI::DragValue<float>("Orthographic Size", Settings.OrthoSize);
        } else
        {
            UI::DragValue<float>("Field Of View", Settings.FieldOfView);
        }
    }

    Matrix4 Camera::GetViewMatrix() const
    {
        return m_Entity->GetTransform()->GetWorldSpaceMatrix().Inverse();
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

