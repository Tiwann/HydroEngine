#include "HydroPCH.h"
#include "Random.h"

#include <random>

namespace Hydro
{
    std::random_device Random::s_RandomDevice;
    
    Color Random::Color()
    {
        const float Red = Float(0.0f, 1.0f);
        const float Green = Float(0.0f, 1.0f);
        const float Blue = Float(0.0f, 1.0f);
        return {Red, Green, Blue, 1.0f};
    }

    float Random::Float(float Min, float Max)
    {
        std::uniform_real_distribution Distribution(Min, Max);
        return Distribution(s_RandomDevice);
    }

    int32_t Random::Integer(int32_t Min, int32_t Max)
    {
        std::uniform_int_distribution Distribution(Min, Max);
        return Distribution(s_RandomDevice);
    }

    glm::vec2 Random::Vector2(glm::vec2::value_type MinX, glm::vec2::value_type MaxX, glm::vec2::value_type MinY,
        glm::vec2::value_type MaxY)
    {
        return { Float(MinX, MaxX), Float(MinY, MaxY) };
    }

    Rectangle Random::Rect(glm::vec2 MinPos, glm::vec2 MaxPos, glm::vec2 MinMaxWidth, glm::vec2 MinMaxHeight)
    {
        Rectangle Rect;
        Rect.X = Float(MinPos.x, MaxPos.x);
        Rect.Y = Float(MinPos.y, MaxPos.y);
        Rect.Width = Float(MinMaxWidth.x, MinMaxWidth.y);
        Rect.Height = Float(MinMaxHeight.x, MinMaxHeight.y);
        return Rect;
    }
}
