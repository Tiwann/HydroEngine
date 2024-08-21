#include "Core/Physics/PhysicsBody2D.h"

#include <box2d/b2_body.h>

namespace Hydro
{
    void PhysicsBody2D::SetUserPointer(void* User)
    {
        b2Body* BodyHandle = GetHandleAs<b2Body>();
        b2BodyUserData& UserData = BodyHandle->GetUserData();
        UserData.pointer = (uintptr_t)User;
    }

    void* PhysicsBody2D::GetUserPointer() const
    {
        const b2Body* BodyHandle = GetHandleAs<b2Body>();
        const b2BodyUserData& UserData = BodyHandle->GetUserData();
        return (void*)UserData.pointer;
    }
}
