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

    Vector2 Random::Vector2(float MinX, float MaxX, float MinY, float MaxY)
    {
        return { Float(MinX, MaxX), Float(MinY, MaxY) };
    }
}
