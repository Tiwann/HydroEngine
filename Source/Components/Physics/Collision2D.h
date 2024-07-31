#pragma once
#include "Core/SharedPointer.h"
#include "Math/Vector2.h"

namespace Hydro
{
    class Shape2D;
    
    struct Collision2D
    {
        Vector2 ImpactPoint;
        Vector2 Normal;
        Ref<Shape2D> OtherCollider;
    };
}
