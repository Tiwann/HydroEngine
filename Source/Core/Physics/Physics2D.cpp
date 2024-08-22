#include "HydroPCH.h"
#include "Core/Physics/Physics2D.h"
#include "Core/Misc.h"


namespace Hydro
{
    Vector2 Physics2D::Gravity = { 0.0f, -9.81f };
    float Physics2D::TimeStep = FPS<float>(60);
    
    bool Physics2D::CheckCircle(const Vector3& Center, float Radius)
    {
       return false;
    }

    RaycastHit2D Physics2D::Raycast(const Ray& Ray, float Distance)
    {
        return {};
    }
}
