#pragma once
#include "Core/TypeTraits.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace Hydro
{
    template<typename T, typename = EnableIfType<IsVectorValue<T>>>
    struct TangentPoint
    {
        using VectorType = T;
        T Position;
        T Direction;
    };

    using TangentPoint2D = TangentPoint<Vector2>;
    using TangentPoint3D = TangentPoint<Vector3>;
}
