#pragma once
#include "Math/Vector3.h"

namespace Hydro
{
    template<typename BodyType>
    struct PhysicsContactInfo
    {
        Vector3 Point;
        Vector3 Normal;
        BodyType* OtherBody;
    };
}