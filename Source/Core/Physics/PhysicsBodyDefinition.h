#pragma once
#include "Math/Vector3.h"
#include "PhysicsBodyType.h"

namespace Hydro
{
    struct PhysicsBodyDefinition
    {
        Vector3 Position;
        Vector3 Rotation;
        PhysicsBodyType Type;
    };
}
