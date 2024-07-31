#pragma once
#include "Core/Flags.h"

namespace Hydro
{
    enum class PhysicsConstraintsBits
    {
        None = 0,
        HYDRO_FLAG_BIT(PositionX, 0),
        HYDRO_FLAG_BIT(PositionY, 1),
        HYDRO_FLAG_BIT(PositionZ, 2),
        HYDRO_FLAG_BIT(RotationX, 3),
        HYDRO_FLAG_BIT(RotationY, 4),
        HYDRO_FLAG_BIT(RotationZ, 5),
        Position = PositionX | PositionY | PositionZ,
        Rotation = RotationX | RotationY | RotationZ,
        All = Position | Rotation,
    };

    using PhysicsConstraintsFlags = Flags<PhysicsConstraintsBits>;
}
