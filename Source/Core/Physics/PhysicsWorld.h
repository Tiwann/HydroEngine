#pragma once
#include "Core/Physics/PhysicsBody.h"
#include "Core/Physics/PhysicsBodyDefinition.h"

namespace Hydro
{
    class PhysicsWorld
    {
    public:
        virtual ~PhysicsWorld() = default;
        virtual void OnInit() = 0;
        virtual void Step(float TimeStep) = 0;
        virtual void OnDestroy() = 0;

        virtual PhysicsBody* CreateBody(const PhysicsBodyDefinition& Definition) = 0;
        virtual void DestroyBody(PhysicsBody* Body) = 0;
    };
    
}
