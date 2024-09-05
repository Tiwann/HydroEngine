#include "Core/Physics/PhysicsWorld2D.h"
#include "Core/Physics/PhysicsBody2D.h"
#include "Core/Physics/Physics2D.h"
#include "PhysicsWorld2DContactListener.h"
#include "Core/Time.h"
#include "Math/Functions.h"
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

#include "Core/Log.h"
#include "Core/LogVerbosity.h"

namespace Hydro
{
    void PhysicsWorld2D::OnInit()
    {
        m_World = new b2World(Physics2D::Gravity);
        m_ContactListener = new PhysicsWorld2DContactListener(this);
        m_World->SetContactListener(m_ContactListener);
    }

    void PhysicsWorld2D::Step(const f32 TimeStep)
    {
        m_World->Step(TimeStep * Time::Scale, 8, 3);
    }

    void PhysicsWorld2D::OnDestroy()
    {
        delete m_ContactListener;
        delete m_World;
    }

    void PhysicsWorld2D::OnContactBegin(PhysicsBody2D* BodyA, PhysicsBody2D* BodyB)
    {
        HYDRO_LOG(Physics2D, Verbosity::Info, "Contact between two bodies started!");

        if(BodyA->IsSensor() || BodyB->IsSensor()) return;
            
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

    void PhysicsWorld2D::OnContactEnd(PhysicsBody2D* BodyA, PhysicsBody2D* BodyB)
    {
        HYDRO_LOG(Physics2D, Verbosity::Info, "Contact between two bodies ended!");
    }

    PhysicsBody2D* PhysicsWorld2D::CreateBody(const PhysicsBodyDefinition& Definition, const PhysicsMaterial& Material)
    {
        b2BodyDef BodyDefinition{};
        BodyDefinition.position = (Vector2)Definition.Position;
        BodyDefinition.angle = Math::Radians(Definition.Rotation.z);
        BodyDefinition.type = (b2BodyType)Definition.Type;
        
        b2Body* BodyHandle = m_World->CreateBody(&BodyDefinition);
        PhysicsBody2D* CreatedBody = new PhysicsBody2D(BodyHandle, *this);
        m_Bodies.Add(CreatedBody);
        return CreatedBody;
    }

    void PhysicsWorld2D::DestroyBody(PhysicsBody2D* Body)
    {
        m_World->DestroyBody(Body->GetHandle());
        m_Bodies.Remove(Body);
        delete Body;
        Body = nullptr;
    }

    void PhysicsWorld2D::SetMaterial(PhysicsBody2D* Body, const PhysicsMaterial& Material)
    {
        Body->SetMaterial(Material);
    }
}
