#pragma once
#include "PhysicsShape.h"
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

namespace Hydro
{
    class PhysicsShape3D : public PhysicsShape<JPH::Shape>
    {
    public:
        using HandleType = PhysicsShape::HandleType;
        PhysicsShape3D() : PhysicsShape() { }
    };
}
