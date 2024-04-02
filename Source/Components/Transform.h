#pragma once
#include "Core/Component.h"
#include "Math/LinearAlgebra.h"
namespace Hydro
{
    class Transform : public Component
    {
    public:
        Transform();
        
        const Vector3& GetPosition() const;
        const Vector3& GetRotation() const;
        const Vector3& GetScale() const;

        void SetPosition(const Vector3& Position);
        void SetRotation(const Vector3& Rotation);
        void SetScale(const Vector3& Scale);
        
        
        void Translate(const Vector3& Translation);
        void Translate(float X, float Y, float Z);
        void Rotate(const Vector3& EulerAngles);
        void Scale(const Vector3& Vector);
        void Scale(float Scalar);

        Vector3 GetForwardVector() const;
        Vector3 GetRightVector() const;
        Vector3 GetUpVector() const;
        
        Matrix4 GetMatrix() const;
    
    private:
        Vector3 m_Position{Vector3::Zero};
        Vector3 m_Rotation{Vector3::Zero};
        Vector3 m_Scale{Vector3::One};
    };

    
}
