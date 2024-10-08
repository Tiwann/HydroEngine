﻿#include "Circle2D.h"
#include "Components/Transform.h"
#include "Core/Color.h"
#include "Core/RendererBackend.h"
#include "Core/Physics/PhysicsShape.h"
#include "Editor/EditorGUI.h"
#include "Core/Physics/PhysicsBody2D.h"
#include "Core/Physics/CircleShape2D.h"


namespace Hydro
{
    Circle2D::Circle2D(Entity* Owner) : RigidBody2D(Owner, "Circle 2D")
    {
        
    }

    void Circle2D::OnInspectorGUI(const ImGuiIO& IO)
    {
        RigidBody2D::OnInspectorGUI(IO);
        UI::DragVector2<f32>("Center", m_Center);
        UI::DragValue<f32>("Radius", m_Radius);
        const char* ColliderTypes[3] = { "Static", "Kinematic", "Dynamic" };

        PhysicsBodyType BodyType = m_PhysicsBody->GetType();
        if(ImGui::Combo("Collider Type", (int*)&BodyType, ColliderTypes, 3))
        {
            m_PhysicsBody->SetType(BodyType);
        }
    }

    PhysicsShape2D* Circle2D::CreateShape(Ref<Transform> Transform)
    {
        return new CircleShape2D(m_Radius, m_Center);
    }

    Vector2 Circle2D::GetCenter() const
    {
        return m_Center;
    }

    void Circle2D::SetCenter(const Vector2& Center)
    {
        m_Center = Center;
    }

    f32 Circle2D::GetRadius() const
    {
        return m_Radius;
    }

    void Circle2D::SetRadius(f32 radius)
    {
        m_Radius = radius;
    }
    
    void Circle2D::RenderCollisions(const Ref<RendererBackend>& Renderer) const
    {
        const Matrix4 Transform = GetTransform()->GetWorldSpaceMatrix();
        Renderer->DrawCircle(Transform, m_Center, m_Radius, Color::Green);
    }
}
