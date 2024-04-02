#pragma once
//#include "glm/vec2.hpp"
//#include "glm/vec3.hpp"
//#include "glm/vec4.hpp"
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