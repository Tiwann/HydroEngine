#pragma once
#include "LogCategory.h"
#include "Math/Vector2.h"
#include "Core/RaycastHit.h"

#define HYDRO_EARTH_GRAVITY (-9.81f)
HYDRO_DECLARE_LOG_CATEGORY_STATIC(Box2D, "BOX2D")

namespace Hydro
{
    class Vector2;
    class Vector3;
    struct Ray;
    
    class Physics2D
    {
    public:
        static Vector2 Gravity;
        static float TimeStep;
        
        static bool CheckCircle(const Vector3& Center, float Radius);
        static RaycastHit2D Raycast(const Ray& Ray, float Distance);
    };
}
