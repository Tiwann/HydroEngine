#include "Core/Physics/Physics3D.h"

namespace Hydro
{
    Vector3 Physics3D::Gravity = { 0.0f, -9.81f, 0.0f };
    float Physics3D::TimeStep = 1.0f / 60.0f;
}
