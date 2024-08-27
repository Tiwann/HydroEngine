#pragma once
#include "PhysicsShape3D.h"

namespace Hydro
{
    class SphereShape3D : public PhysicsShape3D
    {
    public:
        explicit SphereShape3D(float Radius);
    private:
        float m_Radius;
    };
}
