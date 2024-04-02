#include "HydroPCH.h"
#include "Collider2D.h"

#include <box2d/b2_world.h>
#include <box2d/b2_math.h>
#include "Core/Scene.h"
#include "Components/Transform.h"

namespace Hydro
{
    Collider2D::Collider2D(const std::string& Name) : Component(Name)
    {
        
    }
    

    void Collider2D::OnInit()
    {
        Component::OnInit();

        const Vector3 Position = GetTransform()->GetPosition();
        const Vector3 Rotation = GetTransform()->GetRotation();
        m_BodyDef.position = {Position.x, Position.y};
        m_BodyDef.angle = Math::Radians(Rotation.z);
        m_BodyDef.type = (b2BodyType)Type;

        m_Body = m_GameObject->GetScene().m_Physics2DWorld->CreateBody(&m_BodyDef);

        m_Shape = CreateShape();
        m_FixtureDef.shape = m_Shape;
        m_FixtureDef.density = Material.Density;
        m_FixtureDef.friction = Material.Friction;
        m_FixtureDef.restitution = Material.Elasticity;
        m_Body->CreateFixture(&m_FixtureDef);
    }

    void Collider2D::OnDestroy()
    {
        m_GameObject->GetScene().m_Physics2DWorld->DestroyBody(m_Body);
        delete m_Shape;
    }

    void Collider2D::OnPhysicsUpdate(float Delta)
    {
        const Ref<Transform> Trans = GetTransform();
        
        b2Vec2 Position = m_Body->GetPosition();
        Trans->SetPosition({Position.x, Position.y, Trans->GetPosition().z});
        Trans->SetRotation({0.0f, 0.0f, m_Body->GetAngle()});
    }
}
