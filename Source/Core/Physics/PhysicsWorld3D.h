#pragma once
#include "Core/Physics/PhysicsWorld.h"

#include <Jolt/Jolt.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>

namespace Hydro
{
    
    class PhysicsWorld3D : public PhysicsWorld
    {
    public:
        PhysicsWorld3D();
        void OnInit() override;
        void Step(float TimeStep) override;
        void OnDestroy() override;

        PhysicsBody* CreateBody(const PhysicsBodyDefinition& Definition) override;
        void DestroyBody(PhysicsBody* Body) override;
    private:
        JPH::TempAllocatorImpl m_TempAllocator;
        JPH::JobSystemThreadPool m_JobSystem;
        JPH::PhysicsSystem m_System;
    };
}
