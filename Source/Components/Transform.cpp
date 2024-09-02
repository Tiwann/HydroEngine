﻿#include "Transform.h"
#include "Core/Entity.h"
#include "Editor/EditorGUI.h"
#include "Physics/PhysicsComponent.h"
#include "Physics/RigidBody2D.h"

namespace Hydro
{
    Transform::Transform(Entity* Owner) : Component(Owner, "Transform")
    {
    }

    void Transform::OnDestroy()
    {
        Component::OnDestroy();
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

    void Transform::SetPosition(f32 X, f32 Y, f32 Z)
    {
        SetPosition({X, Y, Z});
    }

    void Transform::SetRotation(f32 X, f32 Y, f32 Z)
    {
        SetRotation({X, Y, Z});
    }

    void Transform::SetScale(f32 X, f32 Y, f32 Z)
    {
        SetScale({X, Y, Z});
    }

    void Transform::SetScale(f32 UniformScale)
    {
        SetScale({UniformScale, UniformScale, UniformScale});
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
        if(m_Entity->GetComponent<RigidBody2D>() && Translation != Vector3::Zero)
        {
            HYDRO_LOG(Transform, Verbosity::Warning, "Tried to translate an object that is controlled by physics.");
        }
        m_Position += Translation;
    }

    void Transform::Translate(f32 X, f32 Y, f32 Z)
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

    void Transform::Scale(f32 Scalar)
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

    Matrix4 Transform::GetWorldSpaceMatrix() const
    {
        if(m_Entity->HasParent())
        {
            return m_Entity->GetParent()->GetTransform()->GetWorldSpaceMatrix() * GetLocalSpaceMatrix();
        }
        return GetLocalSpaceMatrix();
    }

    Matrix4 Transform::GetLocalSpaceMatrix() const
    {
        Matrix4 Result = Matrix4::Identity;
        Result.Scale(m_Scale);
        Result.RotateDegrees(m_Rotation);
        Result.Translate(m_Position);
        return Result;
    }

    void Transform::OnInspectorGUI(const ImGuiIO& IO)
    {
        Component::OnInspectorGUI(IO);
        
        if(UI::DragVector3<f32>("Position", m_Position, 0.01f, 0, 0, "%.2f"))
        {
            if(const auto& Shape = m_Entity->GetComponent<RigidBody2D>())
            {
                Shape->SetPosition(m_Position);
                Shape->RecreatePhysicsState();
            }
        }
        
        if(UI::DragVector3<f32>("Rotation", m_Rotation, 0.01f, 0, 360.0f, "%.2f"))
        {
            if(const auto& Shape = m_Entity->GetComponent<RigidBody2D>())
            {
                Shape->SetRotation(m_Rotation.z);
                Shape->RecreatePhysicsState();
            }
        }
        
        if(UI::DragVector3<f32>("Scale", m_Scale, 0.01f, 0, 0, "%.2f"))
        {
            if(const auto& Shape = m_Entity->GetComponent<RigidBody2D>())
            {
                Shape->RecreatePhysicsState();
            }
        }
    }
}

