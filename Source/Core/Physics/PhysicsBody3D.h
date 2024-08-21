#pragma once
#include "Core/Physics/PhysicsBody.h"

namespace Hydro
{
    class PhysicsBody3D : public PhysicsBody
    {
    public:
        PhysicsBody3D(uintptr_t Handle, PhysicsWorld& World) : PhysicsBody(Handle, World) { }
        
        void SetUserPointer(void* User) override;
        void* GetUserPointer() const override;
    };
}
