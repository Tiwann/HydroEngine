#include "HydroPCH.h"
#include "Box2D.h"
#include "Core/Scene.h"
#include "Components/Transform.h"
#include "Core/RendererBackend.h"

#include <box2d/b2_polygon_shape.h>

#include "Core/Color.h"
#include "Editor/EditorGUI.h"

static constexpr char ComponentName[7] = "Box 2D";

namespace Hydro
{
    Box2D::Box2D(GameObject* Owner) : Shape2D(Owner, ComponentName)
    {
        
    }

    void Box2D::OnInspectorGUI(const ImGuiIO& IO)
    {
        Shape2D::OnInspectorGUI(IO);
        
        UI::DragVector2<float>("Center", m_Center);
        UI::DragVector2<float>("Half Extents", m_HalfExtents);
        const char* ColliderTypes[3] = { "Static", "Kinematic", "Dynamic" };
        
        if(ImGui::Combo("Collider Type", (int*)&m_Type, ColliderTypes, 3))
        {
            RecreateFixture();
        }
    }


    Vector2 Box2D::GetCenter() const
    {
        return m_Center;
    }

    void Box2D::SetCenter(const Vector2& Center)
    {
        m_Center = Center;
    }

    Vector2 Box2D::GetHalfExtents() const
    {
        return m_HalfExtents;
    }

    void Box2D::SetHalfExtents(const Vector2& HalfExtents)
    {
        m_HalfExtents = HalfExtents;
    }

    b2Shape* Box2D::CreateShape()
    {
        b2PolygonShape* Shape = new b2PolygonShape;
        const Vector3 Extents = m_HalfExtents;
        const Vector3 TransformedExtents = GetTransform()->GetWorldSpaceMatrix() * Extents;
        const float ZRotation = GetTransform()->GetRotation().z;
        Shape->SetAsBox(TransformedExtents.x, TransformedExtents.y, m_Center, ZRotation);
        return Shape;
    }

    void Box2D::OnPhysicsUpdate(float Delta)
    {
        Shape2D::OnPhysicsUpdate(Delta);
    }

    void Box2D::RenderCollisions(const Ref<RendererBackend>& Renderer) const
    {
        Vector3 TransformedCenter = GetTransform()->GetPosition() + m_Center;
        Vector3 TransformedExtents = GetTransform()->GetWorldSpaceMatrix() * Vector3(m_HalfExtents);
        Renderer->DrawWireQuad(TransformedCenter,  TransformedExtents , 3.0f, Color::Green);
    }
}
