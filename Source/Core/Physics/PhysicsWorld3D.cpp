#include "Core/Physics/PhysicsWorld3D.h"
#include "Core/Physics/Physics3D.h"
#include "Core/Physics/PhysicsBody3D.h"
#include "Core/Time.h"
#include "Core/Memory.h"

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

namespace Hydro
{
    PhysicsWorld3D::PhysicsWorld3D()
    : m_TempAllocator(10 * 1024 * 1024),
    m_JobSystem(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, (int)(std::thread::hardware_concurrency() - 1))
    {
        
    }

    void PhysicsWorld3D::OnInit()
    {
        JPH::RegisterDefaultAllocator();
        JPH::Factory::sInstance = Memory::Malloc<JPH::Factory>();
        JPH::RegisterTypes();
        
        const JPH::Vec3 Gravity = { Physics3D::Gravity.x, Physics3D::Gravity.y, Physics3D::Gravity.z };
        m_System.SetGravity(Gravity);
        
        /*m_System->Init(Physics3D::MaxBodies,
            0,
            Physics3D::MaxBodyPairs,
            Physics3D::MaxContactConstraints,
            *m_BroadPhaseLayerInterface,
            *m_ObjectVsBroadPhaseLayerFilter,
            *m_ObjectLayerPairFilter);*/
        
    }

    void PhysicsWorld3D::Step(const float TimeStep)
    {
        m_System.Update(TimeStep * Time::Scale, 2, &m_TempAllocator, &m_JobSystem);
    }

    void PhysicsWorld3D::OnDestroy()
    {
        JPH::UnregisterTypes();
        
        Memory::Free(JPH::Factory::sInstance);
        JPH::Factory::sInstance = nullptr;
    }

    PhysicsBody* PhysicsWorld3D::CreateBody(const PhysicsBodyDefinition& Definition)
    {
        JPH::BodyInterface& BodyInterface = m_System.GetBodyInterface();
        JPH::BodyCreationSettings Settings;
        Settings.mPosition = Definition.Position;
        Settings.mRotation = JPH::Quat::sEulerAngles(Definition.Rotation);
        Settings.mMotionType = (JPH::EMotionType)Definition.Type;
        
        const JPH::Body* BodyHandle = BodyInterface.CreateBody(Settings);
        BodyInterface.AddBody(BodyHandle->GetID(), JPH::EActivation::Activate);
        return new PhysicsBody3D((uintptr_t)BodyHandle, *this);
    }

    void PhysicsWorld3D::DestroyBody(PhysicsBody* Body)
    {
        JPH::BodyInterface& BodyInterface = m_System.GetBodyInterface();
        const JPH::Body* BodyHandle = Body->GetHandleAs<JPH::Body>();
        const JPH::BodyID& BodyId = BodyHandle->GetID();
        BodyInterface.RemoveBody(BodyId);
        BodyInterface.DestroyBody(BodyId);
        delete Body;
        Body = nullptr;
    }
}

