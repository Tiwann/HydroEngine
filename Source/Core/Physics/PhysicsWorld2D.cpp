#include "Core/Physics/PhysicsWorld2D.h"
#include "Core/Physics/PhysicsBody2D.h"
#include "Core/Physics/Physics2D.h"
#include "Core/Time.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

#include "PhysicsBody3D.h"

namespace Hydro
{
    void PhysicsWorld2D::OnInit()
    {
        m_World = new b2World(Physics2D::Gravity);
    }

    void PhysicsWorld2D::Step(const float TimeStep)
    {
        m_World->Step(TimeStep * Time::Scale, 8, 3);
    }

    void PhysicsWorld2D::OnDestroy()
    {
        delete m_World;
    }

    PhysicsBody2D* PhysicsWorld2D::CreateBody(const PhysicsBodyDefinition& Definition, const PhysicsMaterial& Material)
    {
        b2BodyDef BodyDefinition{};
        BodyDefinition.position = (Vector2)Definition.Position;
        BodyDefinition.angle = Math::Radians(Definition.Rotation.z);
        BodyDefinition.type = (b2BodyType)Definition.Type;
        b2Body* BodyHandle = m_World->CreateBody(&BodyDefinition);
        PhysicsBody2D* CreatedBody = new PhysicsBody2D((uintptr_t)BodyHandle, *this);
        m_Bodies.Add(CreatedBody);
        return CreatedBody;
    }

    void PhysicsWorld2D::DestroyBody(PhysicsBody2D* Body)
    {
        b2Body* BodyHandle = Body->GetHandleAs<b2Body>();
        m_World->DestroyBody(BodyHandle);
        m_Bodies.Remove(Body);
        delete Body;
        Body = nullptr;
    }

    void PhysicsWorld2D::SetMaterial(PhysicsBody2D* Body, const PhysicsMaterial& Material)
    {
        Body->SetMaterial(Material);
    }
}
