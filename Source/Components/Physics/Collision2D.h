#pragma once
#include "Core/SharedPointer.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class RigidBody2D;
    
    struct Collision2D
    {
        Vector2 ImpactPoint;
        Vector2 Normal;
        Ref<RigidBody2D> OtherCollider;
    };
}
