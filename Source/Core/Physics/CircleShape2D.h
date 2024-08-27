#pragma once
#include "PhysicsShape2D.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class CircleShape2D : public PhysicsShape2D
    {
    public:
        explicit CircleShape2D(float Radius, const Vector2& Center);
    private:
        float m_Radius;
        Vector2 m_Center;
    };
}
