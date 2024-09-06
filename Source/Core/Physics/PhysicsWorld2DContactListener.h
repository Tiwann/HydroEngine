#pragma once
#include "Core/Shape2DContactListener.h"

namespace Hydro
{
    class PhysicsWorld2D;
    class PhysicsBody2D;
    
    class PhysicsWorld2DContactListener : public b2ContactListener
    {
    public:
        PhysicsWorld2DContactListener(PhysicsWorld2D* World);
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;

    private:
        PhysicsWorld2D* m_World = nullptr;
    };
}


