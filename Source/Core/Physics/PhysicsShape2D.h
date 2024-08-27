#pragma once
#include "PhysicsShape.h"
#include <box2d/b2_shape.h>

namespace Hydro
{
    class PhysicsShape2D : public PhysicsShape<b2Shape>
    {
    public:
        PhysicsShape2D() : PhysicsShape() {}
        using HandleType = PhysicsShape::HandleType;
    };
}
