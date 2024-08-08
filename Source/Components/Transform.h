#pragma once
#include "Core/Component.h"
#include "Core/MulticastDelegate.h"
#include "Math/LinearAlgebra.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Transform, "TRANSFORM")

namespace Hydro
{
    class Transform : public Component
    {
    public:
        Transform(GameObject* Owner);

        void OnDestroy() override;
        
        const Vector3& GetPosition() const;
        const Vector3& GetRotation() const;
        const Vector3& GetScale() const;

        void SetPosition(const Vector3& Position);
        void SetPosition(float X, float Y, float Z);
        void SetRotation(const Vector3& Rotation);
        void SetRotation(float X, float Y, float Z);
        void SetScale(const Vector3& Scale);
        void SetScale(float X, float Y, float Z);
        void SetScale(float UniformScale);
        
        void Translate(const Vector3& Translation);
        void Translate(float X, float Y, float Z);
        void Rotate(const Vector3& EulerAngles);
        void Scale(const Vector3& Vector);
        void Scale(float Scalar);

        Vector3 GetForwardVector() const;
        Vector3 GetRightVector() const;
        Vector3 GetUpVector() const;

        
        Matrix4 GetWorldSpaceMatrix() const;
        Matrix4 GetLocalSpaceMatrix() const;
        void OnInspectorGUI(const ImGuiIO& IO) override;

        using ScaleSetDelegate = MulticastDelegate<void(const Transform*)>;
        ScaleSetDelegate OnScaleSet;
    private:
        Vector3 m_Position{Vector3::Zero};
        Vector3 m_Rotation{Vector3::Zero};
        Vector3 m_Scale{Vector3::One};
    };

    
}
