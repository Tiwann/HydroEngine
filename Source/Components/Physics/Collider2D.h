#pragma once
#include "ColliderType.h"
#include "Core/Component.h"
#include "Core/MulticastDelegate.h"

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "Core/PhysicsMaterial.h"

namespace Hydro
{
    struct Collision2D;
    using CollisionDelegate = MulticastDelegate<const Collision2D&>;
    
    class Collider2D : public Component
    {
    public:
        CollisionDelegate OnCollisionEnter;
        CollisionDelegate OnCollisionStay;
        CollisionDelegate OnCollisionExit;
        
        ColliderType Type{Static};
        PhysicsMaterial Material;
    protected:
        Collider2D(const std::string& Name);
        virtual void OnCollisionEnterImplementation(const Collision2D& Collision) = 0;
        virtual void OnCollisionStayImplementation(const Collision2D& Collision) = 0;
        virtual void OnCollisionExitImplementation(const Collision2D& Collision) = 0;
        virtual b2Shape* CreateShape() = 0;
        
        void OnInit() override;
        void OnDestroy() override;
        void OnPhysicsUpdate(float Delta) override;
        
        
        b2BodyDef m_BodyDef;
        b2Body* m_Body;
        b2Shape* m_Shape;
        b2FixtureDef m_FixtureDef;
        b2Fixture* m_Fixture;
    };
}
