#pragma once
#include "Core/Component.h"
#include "Core/CameraProjectionType.h"
#include "Core/CameraSettings.h"
#include "Core/Log.h"
#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Camera, "CAMERA");

namespace Hydro
{
    class Matrix4;
    
    class Camera : public Component
    {
    public:
        Camera(const CameraSettings& Settings);

        void OnUpdate(float Delta) override;

        float GetWidth() const { return m_Settings.Width; }
        float GetHeight() const { return m_Settings.Height; }
        CameraProjectionType GetProjectionType() const { return m_Settings.Projection; }
        float GetFOV() const { return m_Settings.FieldOfView; }
        float GetOrthoSize() const { return m_Settings.OrthoSize; }
        float GetNearPlane() const { return m_Settings.NearPlane; }
        float GetFarPlane() const { return m_Settings.FarPlane; }

        Matrix4 GetViewMatrix() const;
        Matrix4 GetProjectionMatrix() const;
    private:
        CameraSettings m_Settings;
    };
}
