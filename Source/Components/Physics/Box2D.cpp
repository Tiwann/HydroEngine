#include "HydroPCH.h"
#include "Box2D.h"
#include "Core/Scene.h"
#include "Components/Transform.h"
#include "Core/RendererBackend.h"
#include "Core/Color.h"
#include "Core/Physics/PhysicsShape.h"
#include "Editor/EditorGUI.h"

static constexpr char ComponentName[7] = "Box 2D";

namespace Hydro
{
    Box2D::Box2D(GameObject* Owner) : RigidBody2D(Owner, ComponentName)
    {
        
    }

    PhysicsShape2D* Box2D::CreateShape()
    {
        return new BoxShape2D(m_HalfExtents, m_Center, 0.0f);
    }

    void Box2D::OnInspectorGUI(const ImGuiIO& IO)
    {
        RigidBody2D::OnInspectorGUI(IO);
        
        UI::DragVector2<float>("Center", m_Center, 0.01f);
        UI::DragVector2<float>("Half Extents", m_HalfExtents, 0.01f);
        StaticArray<const char*, 3> BodyTypes = { "Static", "Kinematic", "Dynamic" };
        
        if(ImGui::Combo("Collider Type", (int*)&m_Type, BodyTypes.Data(), 3))
        {
            RecreatePhysicsState();
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
    
    void Box2D::RenderCollisions(const Ref<RendererBackend>& Renderer) const
    {
        Vector3 TransformedCenter = GetTransform()->GetPosition() + m_Center;
        Vector3 TransformedExtents = GetTransform()->GetWorldSpaceMatrix() * Vector3(m_HalfExtents);
        Renderer->DrawWireQuad(TransformedCenter,  TransformedExtents , 3.0f, Color::Green);
    }
}
