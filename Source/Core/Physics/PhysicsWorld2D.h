#pragma once
#include "Core/Physics/PhysicsWorld.h"

class b2World;

namespace Hydro
{
    class PhysicsBody2D;
    class PhysicsShape2D;
    class PhysicsWorld2DContactListener;
    struct PhysicsContact2D;
    
    class PhysicsWorld2D : public PhysicsWorld<PhysicsBody2D, PhysicsShape2D, PhysicsContact2D>
    {
    public:
        void OnInit() override;
        void Step(f32 TimeStep) override;
        void OnDestroy() override;
        
        void OnContactBegin(const PhysicsContact2D* Contact) override;
        void OnContactStay(const PhysicsContact2D* Contact) override;
        void OnContactEnd(const PhysicsContact2D* Contact) override;
        
        PhysicsBody2D* CreateBody(const PhysicsBodyDefinition& Definition, const PhysicsMaterial& Material) override;
        void DestroyBody(PhysicsBody2D* Body) override;
        void SetMaterial(PhysicsBody2D* Body, const PhysicsMaterial& Material) override;
    
    private:
        b2World* m_World = nullptr;
        PhysicsWorld2DContactListener* m_ContactListener = nullptr;
    };
}
