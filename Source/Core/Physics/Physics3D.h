#pragma once
#include "Math/Vector3.h"

namespace Hydro
{
    class Physics3D
    {
    public:
        static Vector3 Gravity;
        static float TimeStep;
        static constexpr uint32_t MaxBodies = 0xFFFFui32;
        static constexpr uint32_t MaxBodyPairs = 0xFFFFui32;
        static constexpr uint32_t MaxContactConstraints = 10240;
        
    };
}
