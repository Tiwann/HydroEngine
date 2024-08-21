#pragma once
#include "Core/Physics/PhysicsBody.h"

namespace Hydro
{
    class PhysicsBody2D : public PhysicsBody
    {
    public:
        PhysicsBody2D(uintptr_t Handle, PhysicsWorld& World) : PhysicsBody(Handle, World) { }

        void SetUserPointer(void* User) override;
        void* GetUserPointer() const override;
    };
}
