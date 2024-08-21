#include "Core/Physics/PhysicsWorld2D.h"
#include "Core/Physics/Physics2D.h"
#include "Core/Time.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

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

    PhysicsBody* PhysicsWorld2D::CreateBody(const PhysicsBodyDefinition& Definition)
    {
        b2BodyDef Def;
        Def.position = (Vector2)Definition.Position;
        Def.angle = Math::Radians(Definition.Rotation.z);
        Def.type = (b2BodyType)Definition.Type;
        
        b2Body* BodyHandle = m_World->CreateBody(&Def);

        return new PhysicsBody2D((uintptr_t)BodyHandle, *this);
    }

    void PhysicsWorld2D::DestroyBody(PhysicsBody* Body)
    {
        b2Body* BodyHandle = Body->GetHandleAs<b2Body>();
        m_World->DestroyBody(BodyHandle);
        delete Body;
        Body = nullptr;
    }
}
