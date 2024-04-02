#include "HydroPCH.h"
#include "Transform.h"

namespace Hydro
{
    Transform::Transform() : Component("Transform")
    {
    }

    const Vector3& Transform::GetPosition() const
    {
        return m_Position;
    }

    const Vector3& Transform::GetRotation() const
    {
        return m_Rotation;
    }

    const Vector3& Transform::GetScale() const
    {
        return m_Scale;
    }

    void Transform::SetPosition(const Vector3& Position)
    {
        m_Position = Position;
    }

    void Transform::SetRotation(const Vector3& Rotation)
    {
        m_Rotation = Rotation;
    }

    void Transform::SetScale(const Vector3& Scale)
    {
        m_Scale = Scale;
    }

    void Transform::Translate(const Vector3& Translation)
    {
        m_Position += Translation;
    }

    void Transform::Translate(float X, float Y, float Z)
    {
        m_Position += {X, Y, Z};
    }

    void Transform::Rotate(const Vector3& EulerAngles)
    {
        m_Rotation += EulerAngles;
    }

    void Transform::Scale(const Vector3& Vector)
    {
        m_Scale *= Vector;
    }

    void Transform::Scale(float Scalar)
    {
        m_Scale *= Scalar;
    }

    Vector3 Transform::GetForwardVector() const
    {
        return Math::ForwardFromRotation(m_Rotation);
    }

    Vector3 Transform::GetRightVector() const
    {
        return Math::RightFromRotation(m_Rotation);
    }

    Vector3 Transform::GetUpVector() const
    {
        return Math::UpFromRotation(m_Rotation);
    }

    Matrix4 Transform::GetMatrix() const
    {
        Matrix4 Result = Matrix4::Identity;
        Result.Scale(m_Scale);
        Result.Rotate(m_Rotation);
        Result.Translate(m_Position);
        return Result;
    }
}

