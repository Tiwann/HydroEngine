#pragma once

#include <random>

#include "Color.h"
#include <glm/vec2.hpp>
#include "Rectangle.h"

namespace Hydro
{
    class Random
    {
    public:
        static Color Color();
        static float Float(float Min, float Max);
        static int32_t Integer(int32_t Min, int32_t Max);
        static glm::vec2 Vector2(glm::vec2::value_type MinX, glm::vec2::value_type MinY, glm::vec2::value_type MaxX, glm::vec2::value_type MaxY);
        static Rectangle Rect(glm::vec2 MinPos, glm::vec2 MaxPos, glm::vec2 MinMaxWidth, glm::vec2 MinMaxHeight);
    private:
        static std::random_device s_RandomDevice;
        
    };
}
