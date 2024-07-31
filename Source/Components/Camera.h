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
        Camera(GameObject* Owner);

        void OnUpdate(float Delta) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        
        Matrix4 GetViewMatrix() const;
        Matrix4 GetProjectionMatrix() const;
        CameraSettings Settings{};
    };
}

