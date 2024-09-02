#pragma once
#include "Core/NumericTypes.h"

namespace Hydro
{
    class Time
    {
    public:
        static inline f32 Scale = 1.0f;
        static f32 GetTime();
    };
}
