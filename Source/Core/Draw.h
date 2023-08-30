#pragma once
#include "glm/vec2.hpp"
#include "Macros.h"

namespace Hydro
{
    class Color;
    
    class HYDRO_API Draw
    {
    public:
        static void Point(const glm::vec2& Position, float Radius, const Color& Color);
        static void Point(float X, float Y, float Radius, const Color& Color);
    };
}
