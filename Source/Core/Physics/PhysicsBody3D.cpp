#include "Core/Physics/PhysicsBody3D.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>

namespace Hydro
{
    void PhysicsBody3D::SetUserPointer(void* User)
    {
        JPH::Body* BodyHandle = GetHandleAs<JPH::Body>();
        BodyHandle->SetUserData((JPH::uint64)User);
    }

    void* PhysicsBody3D::GetUserPointer() const
    {
        const JPH::Body* BodyHandle = GetHandleAs<JPH::Body>();
        return (void*)BodyHandle->GetUserData();
    }
}
