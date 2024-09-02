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
        static f32 Float(f32 Min, f32 Max);
        static i32 Integer(i32 Min, i32 Max);
        
        static Vector2 Vector2(f32 MinX, f32 MinY, f32 MaxX, f32 MaxY);
    private:
        static std::random_device s_RandomDevice;
        
    };
}
