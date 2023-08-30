#pragma once
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "Macros.h"

namespace Hydro
{
    struct HYDRO_API Vertex
    {
        glm::vec3 Position{};
        glm::vec2 TextureCoordinate{};
        glm::vec3 Normal{};
        glm::vec4 Color{};
    };
}