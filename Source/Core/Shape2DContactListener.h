#pragma once
#include "Components/Physics/RigidBody2D.h"
#include <box2d/b2_world_callbacks.h>

#include <box2d/b2_contact.h>

#include "Components/Physics/Collision2D.h"


namespace Hydro
{
    class Shape2DContactListener : public b2ContactListener
    {
    public:
        void BeginContact(b2Contact* contact) override
        {
            if(!contact->IsTouching())
                return;
            
            RigidBody2D* ColliderA = (RigidBody2D*)contact->GetFixtureA()->GetUserData().pointer;
            RigidBody2D* ColliderB = (RigidBody2D*)contact->GetFixtureB()->GetUserData().pointer;
            if(ColliderA->IsTrigger() || ColliderB->IsTrigger()) return;
            
            b2WorldManifold WorldManifold;
            contact->GetWorldManifold(&WorldManifold);
                
            Collision2D Collision2DA{};
            Collision2DA.ImpactPoint = WorldManifold.points[0];
            Collision2DA.Normal = WorldManifold.normal;
            if(!ColliderA->IsColliding)
            {
                ColliderA->OnCollisionEnterEvent.Broadcast(Collision2DA);
                ColliderA->IsColliding = true;
            } else
            {
                ColliderA->OnCollisionStayEvent.Broadcast(Collision2DA);
            }

            Collision2D Collision2DB{};
            Collision2DB.ImpactPoint = WorldManifold.points[1];
            Collision2DB.Normal = -WorldManifold.normal;
            if(!ColliderB->IsColliding)
            {
                ColliderB->OnCollisionEnterEvent.Broadcast(Collision2DB);
                ColliderB->IsColliding = true;
            } else
            {
                ColliderB->OnCollisionStayEvent.Broadcast(Collision2DB);
            }
        }
        
        void EndContact(b2Contact* contact) override
        {
            if(!contact->IsTouching()) return;

            RigidBody2D* ColliderA = (RigidBody2D*)contact->GetFixtureA()->GetUserData().pointer;
            RigidBody2D* ColliderB = (RigidBody2D*)contact->GetFixtureB()->GetUserData().pointer;
            if(ColliderA->IsTrigger() || ColliderB->IsTrigger()) return;
            
            b2WorldManifold WorldManifold;
            contact->GetWorldManifold(&WorldManifold);
                
            Collision2D Collision2DA{};
            Collision2DA.ImpactPoint = WorldManifold.points[0];
            Collision2DA.Normal = WorldManifold.normal;
            ColliderA->IsColliding = false;
            ColliderA->OnCollisionExitEvent.Broadcast(Collision2DA);

            Collision2D Collision2DB{};
            Collision2DB.ImpactPoint = WorldManifold.points[1];
            Collision2DB.Normal = -WorldManifold.normal;
            ColliderB->IsColliding = false;
            ColliderB->OnCollisionExitEvent.Broadcast(Collision2DB);
        }
    };
}
