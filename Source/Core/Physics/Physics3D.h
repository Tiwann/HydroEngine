#pragma once
#include "Math/Vector3.h"
#include "Core/Types.h"

namespace Hydro
{
    class Physics3D
    {
    public:
        static Vector3 Gravity;
        static float TimeStep;
        static constexpr uint32 MaxBodies = 0xFFFFui32;
        static constexpr uint32 MaxBodyPairs = 0xFFFFui32;
        static constexpr uint32 MaxContactConstraints = 10240;
    };
}
