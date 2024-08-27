#pragma once
#include "PhysicsShape2D.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class BoxShape2D : public PhysicsShape2D
    {
    public:
        explicit BoxShape2D(const Vector2& HalfExtents, const Vector2& Center, float Rotation);
    private:
        Vector2 m_HalfExtents;
        Vector2 m_Center;
        float m_Rotation = 0.0f;
    };
}
