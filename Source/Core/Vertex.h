#pragma once
#include "Math/LinearAlgebra.h"

namespace Hydro
{
    struct Vertex
    {
        Vector3 Position{};
        Vector2 TextureCoordinate{};
        Vector3 Normal{};
        Vector4 Color{};
    };
}