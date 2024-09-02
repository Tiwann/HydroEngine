#include "Core/Physics/Physics2D.h"
#include "Core/Misc.h"


namespace Hydro
{
    Vector2 Physics2D::Gravity = { 0.0f, -9.81f };
    f32 Physics2D::TimeStep = FPS<f32>(60);
    
    bool Physics2D::CheckCircle(const Vector3& Center, f32 Radius)
    {
       return false;
    }

    RaycastHit2D Physics2D::Raycast(const Ray& Ray, f32 Distance)
    {
        return {};
    }
}
