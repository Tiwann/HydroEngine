#pragma once
#include "SharedPointer.h"
#include "Components/Physics/Shape3D.h"
#include "Components/Physics/Shape2D.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Hydro
{
    template<typename Vector, typename Component>
    struct RaycastHit
    {
        Vector Point;
        Vector Normal;
        Vector Location;
        float Fraction;
        float Distance;
        Ref<Component> HitComponent;
    };

    using RaycastHit2D = RaycastHit<Vector2, Shape2D>;
    using RaycastHit3D = RaycastHit<Vector3, Shape3D>;
}
