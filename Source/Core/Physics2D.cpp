#include "HydroPCH.h"
#include "Physics2D.h"

constinit float EarthGravity = -9.81f;

namespace Hydro
{
    Vector2 Physics2D::Gravity = { 0.0f, EarthGravity };
    float Physics2D::TimeStep = 1.0f / 60.0f;
}
