#include "Box2D.h"
#include "Core/Scene.h"
#include "Components/Transform.h"
#include "Core/RendererBackend.h"
#include "Core/Color.h"
#include "Core/Physics/PhysicsBody2D.h"
#include "Core/Physics/BoxShape2D.h"
#include "Editor/EditorGUI.h"

static constexpr char ComponentName[7] = "Box 2D";

namespace Hydro
{
    Box2D::Box2D(Entity* Owner) : RigidBody2D(Owner, ComponentName)
    {
        
    }

    PhysicsShape2D* Box2D::CreateShape(Ref<Transform> EntityTransform)
    {
        const Matrix4 Transform = EntityTransform->GetWorldSpaceMatrix();
        const Vector2 TransformedHalfExtents = Transform * Vector3(m_HalfExtents);
        return new BoxShape2D(TransformedHalfExtents, m_Center, 0.0f);
    }

    void Box2D::OnInspectorGUI(const ImGuiIO& IO)
    {
        RigidBody2D::OnInspectorGUI(IO);
        
        UI::DragVector2<f32>("Center", m_Center, 0.01f);
        UI::DragVector2<f32>("Half Extents", m_HalfExtents, 0.01f);
        StaticArray<const char*, 3> BodyTypes = { "Static", "Kinematic", "Dynamic" };

        PhysicsBodyType BodyType = m_PhysicsBody->GetType();
        if(ImGui::Combo("Collider Type", (int*)&BodyType, BodyTypes.Data(), 3))
        {
            m_PhysicsBody->SetType(BodyType);
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
        const Matrix4 Transform = GetTransform()->GetWorldSpaceMatrix();
        Renderer->DrawWireQuad(Transform, m_Center, m_HalfExtents, 3.0f, Color::Green);
    }
}
