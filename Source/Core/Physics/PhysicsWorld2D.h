#pragma once
#include "Core/Shape2DContactListener.h"
#include "Core/Physics/PhysicsWorld.h"

class b2World;

namespace Hydro
{
    class PhysicsBody2D;
    class PhysicsShape2D;
    class PhysicsWorld2DContactListener;
    
    class PhysicsWorld2D : public PhysicsWorld<PhysicsBody2D, PhysicsShape2D>
    {
    public:
        void OnInit() override;
        void Step(f32 TimeStep) override;
        void OnDestroy() override;
        
        void OnContactBegin(PhysicsBody2D* BodyA, PhysicsBody2D* BodyB) override;
        void OnContactEnd(PhysicsBody2D* BodyA, PhysicsBody2D* BodyB) override;
        
        
        PhysicsBody2D* CreateBody(const PhysicsBodyDefinition& Definition, const PhysicsMaterial& Material) override;
        void DestroyBody(PhysicsBody2D* Body) override;
        void SetMaterial(PhysicsBody2D* Body, const PhysicsMaterial& Material) override;
    
    private:
        b2World* m_World = nullptr;
        PhysicsWorld2DContactListener* m_ContactListener = nullptr;
    };
}
