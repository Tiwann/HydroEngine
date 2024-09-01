#pragma once

#include <random>
#include "Color.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class Random
    {
    public:
        static Color Color();
        static float Float(float Min, float Max);
        static int32 Integer(int32 Min, int32 Max);
        
        static Vector2 Vector2(float MinX, float MinY, float MaxX, float MaxY);
    private:
        static std::random_device s_RandomDevice;
        
    };
}
