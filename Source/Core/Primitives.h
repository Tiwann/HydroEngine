#pragma once
#include "Macros.h"
#include "Vertex.h"
#include <vector>

namespace Hydro
{
    struct HYDRO_API PrimitiveMesh
    {
        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indices;

        static PrimitiveMesh GenerateSphere(float radius, uint32_t num_horizontal, uint32_t latitude);
        static PrimitiveMesh GenerateQuad(float size);

        static PrimitiveMesh BasicSphere;
        static PrimitiveMesh BasicQuad;
    };
}
