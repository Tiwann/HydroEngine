#include "HydroPCH.h"
#include "Circle2D.h"

#include <box2d/b2_circle_shape.h>

#include "Components/Transform.h"
#include "Core/Color.h"
#include "Core/RendererBackend.h"
#include "Editor/EditorGUI.h"


namespace Hydro
{
    Circle2D::Circle2D(GameObject* Owner) : Shape2D(Owner, "Circle 2D")
    {
        
    }

    void Circle2D::OnInspectorGUI(const ImGuiIO& IO)
    {
        Shape2D::OnInspectorGUI(IO);
        UI::DragVector2<float>("Center", m_Center);
        UI::DragValue<float>("Radius", m_Radius);
        const char* ColliderTypes[3] = { "Static", "Kinematic", "Dynamic" };
        
        if(ImGui::Combo("Collider Type", (int*)&m_Type, ColliderTypes, 3))
        {
            RecreatePhysicsState();
        }
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

    void Circle2D::OnPhysicsUpdate(float Delta)
    {
        RecreatePhysicsState();
        Shape2D::OnPhysicsUpdate(Delta);
    }

    b2Shape* Circle2D::CreateShape()
    {
        b2CircleShape* Shape = new b2CircleShape;
        Shape->m_radius = m_Radius;
        return Shape;
    }

    void Circle2D::RenderCollisions(const Ref<RendererBackend>& Renderer) const
    {
        const Vector3 TransformedCenter = GetTransform()->GetPosition() + m_Center;
        Renderer->DrawCircle(TransformedCenter, m_Radius, Color::Green);
    }
}
