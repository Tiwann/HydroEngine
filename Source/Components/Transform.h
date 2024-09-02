﻿#pragma once
#include "Core/Component.h"
#include "Math/LinearAlgebra.h"
#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Transform, "TRANSFORM")

namespace Hydro
{
    class Transform : public Component
    {
    public:
        Transform(Entity* Owner);

        void OnDestroy() override;
        
        const Vector3& GetPosition() const;
        const Vector3& GetRotation() const;
        const Vector3& GetScale() const;

        void SetPosition(const Vector3& Position);
        void SetPosition(f32 X, f32 Y, f32 Z);
        void SetRotation(const Vector3& Rotation);
        void SetRotation(f32 X, f32 Y, f32 Z);
        void SetScale(const Vector3& Scale);
        void SetScale(f32 X, f32 Y, f32 Z);
        void SetScale(f32 UniformScale);
        
        void Translate(const Vector3& Translation);
        void Translate(f32 X, f32 Y, f32 Z);
        void Rotate(const Vector3& EulerAngles);
        void Scale(const Vector3& Vector);
        void Scale(f32 Scalar);

        Vector3 GetForwardVector() const;
        Vector3 GetRightVector() const;
        Vector3 GetUpVector() const;

        
        Matrix4 GetWorldSpaceMatrix() const;
        Matrix4 GetLocalSpaceMatrix() const;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        
    private:
        Vector3 m_Position{Vector3::Zero};
        Vector3 m_Rotation{Vector3::Zero};
        Vector3 m_Scale{Vector3::One};
    };

    
}
