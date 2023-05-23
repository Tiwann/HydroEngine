#pragma once

namespace Hydro
{
    struct HYDRO_API Vertex
    {
        glm::vec3 Position;
        glm::vec2 TextureCoordinate;
        glm::vec3 Normal;
        glm::vec4 Color;
    };
}