#include "HydroPCH.h"
#include "Circle2D.h"

#include "Components/Transform.h"
#include "Core/Color.h"
#include "Core/Memory.h"
#include "Core/RendererBackend.h"
#include "Core/Physics/PhysicsShape.h"
#include "Editor/EditorGUI.h"
#include "Core/Physics/PhysicsBody2D.h"


namespace Hydro
{
    Circle2D::Circle2D(GameObject* Owner) : RigidBody2D(Owner, "Circle 2D")
    {
        
    }

    void Circle2D::OnInspectorGUI(const ImGuiIO& IO)
    {
        RigidBody2D::OnInspectorGUI(IO);
        UI::DragVector2<float>("Center", m_Center);
        UI::DragValue<float>("Radius", m_Radius);
        const char* ColliderTypes[3] = { "Static", "Kinematic", "Dynamic" };

        PhysicsBodyType BodyType = m_PhysicsBody->GetType();
        if(ImGui::Combo("Collider Type", (int*)&BodyType, ColliderTypes, 3))
        {
            m_PhysicsBody->SetType(BodyType);
        }
    }

    PhysicsShape2D* Circle2D::CreateShape()
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

    float Circle2D::GetRadius() const
    {
        return m_Radius;
    }

    void Circle2D::SetRadius(float radius)
    {
        m_Radius = radius;
    }
    
    void Circle2D::RenderCollisions(const Ref<RendererBackend>& Renderer) const
    {
        const Vector3 TransformedCenter = GetTransform()->GetPosition() + m_Center;
        Renderer->DrawCircle(TransformedCenter, m_Radius, Color::Green);
    }
}
