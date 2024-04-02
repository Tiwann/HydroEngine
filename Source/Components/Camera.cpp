#include "HydroPCH.h"
#include "Camera.h"
#include "Math/LinearAlgebra.h"
#include "Transform.h"
#include "Core/Application.h"
#include "Core/GameObject.h"
#include "Core/Assertion.h"
#include "Core/Window.h"

namespace Hydro
{
    Camera::Camera(const CameraSettings& Settings) : Component("Camera"), m_Settings(Settings)
    {                             
    }

    void Camera::OnUpdate(float Delta)
    {
        const Application& App = Application::GetCurrentApplication();
        const Window& Window = App.GetWindow();
        
        m_Settings.Width = (float)Window.GetWidth();
        m_Settings.Height = (float)Window.GetHeight();
    }

    Matrix4 Camera::GetViewMatrix() const
    {
        const Ref<Transform> ObjectTransform = m_GameObject->GetTransform();
        Matrix4 View = ObjectTransform->GetMatrix();
        View.Translate(-ObjectTransform->GetPosition());
        View.Rotate(-ObjectTransform->GetRotation());
        View.Scale(1.0f / ObjectTransform->GetScale());
        return View;
    }

    Matrix4 Camera::GetProjectionMatrix() const
    {
        const float AspectRatio = m_Settings.Width / m_Settings.Height;
        
        const Matrix4 PerspectiveProj = Math::Perspective(
            m_Settings.FieldOfView,
            AspectRatio,
            m_Settings.NearPlane,
            m_Settings.FarPlane);

        const Matrix4 OrthoProj = Math::Orthographic(
            m_Settings.Width,
            m_Settings.Height,
            m_Settings.OrthoSize,
            m_Settings.NearPlane,
            m_Settings.FarPlane);
        
        const Matrix4 Projection = m_Settings.Projection == Perspective ? PerspectiveProj : OrthoProj;
          
        return Projection;
    }
}

