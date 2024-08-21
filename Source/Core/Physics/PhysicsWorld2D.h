#pragma once
#include "Core/Physics/PhysicsWorld.h"

class b2World;

namespace Hydro
{
    class PhysicsWorld2D : public PhysicsWorld
    {
    public:
        void OnInit() override;
        void Step(float TimeStep) override;
        void OnDestroy() override;
        PhysicsBody* CreateBody(const PhysicsBodyDefinition& Definition) override;
        void DestroyBody(PhysicsBody* Body) override;
    private:
        b2World* m_World = nullptr;
    };
}
