#include "PhysicsWorld2DContactListener.h"
#include "PhysicsWorld2D.h"

namespace Hydro
{
    PhysicsWorld2DContactListener::PhysicsWorld2DContactListener(PhysicsWorld2D* World) : m_World(World)
    {
    }

    void PhysicsWorld2DContactListener::BeginContact(b2Contact* contact)
    {
        if(!contact->IsTouching())
            return;
        
        PhysicsBody2D* BodyA = (PhysicsBody2D*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        PhysicsBody2D* BodyB = (PhysicsBody2D*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        m_World->OnContactBegin(BodyA, BodyB);
    }

    void PhysicsWorld2DContactListener::EndContact(b2Contact* contact)
    {
        if(!contact->IsTouching())
            return;
        
        PhysicsBody2D* BodyA = (PhysicsBody2D*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
        PhysicsBody2D* BodyB = (PhysicsBody2D*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
        m_World->OnContactEnd(BodyA, BodyB);
    }
}


