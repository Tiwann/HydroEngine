#pragma once
#include "Core/SharedPointer.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class RigidBody2D;
    
    struct Contact2D
    {
        Vector2 ImpactPoint;
        Vector2 Normal;
        Ref<RigidBody2D> Other;
    };
}
