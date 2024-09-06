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
        
        PhysicsContact2D* Contact = new PhysicsContact2D<b2Contact>;
        Contact->World = m_World;
        Contact->BodyA = BodyA;
        Contact->BodyB = BodyB;
        Contact->ContactData = contact;
        m_World->OnContactBegin(BodyA, BodyB);
        delete Contact;
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


