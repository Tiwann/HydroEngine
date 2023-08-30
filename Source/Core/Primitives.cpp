#include "HydroPCH.h"
#include "Primitives.h"
#include "Utilities.h"

namespace Hydro
{
    PrimitiveMesh PrimitiveMesh::GenerateSphere(float radius, uint32_t num_horizontal, uint32_t num_vertical)
    {
        PrimitiveMesh mesh;
        constexpr float pi = Pi<float>();
        constexpr float pihalf = PiHalf<float>();
        
        for(uint32_t i = 0; i < num_horizontal; i++)
        {
            const float longtitude = Map<float>(i, 0, num_horizontal, -pi, pi);
            for(uint32_t j = 0; j < num_vertical; j++)
            {
                const float latitude = Map<float>(j, 0, num_vertical, -pihalf, pihalf);
                Vertex v;
                v.Position.x = radius * std::sin(longtitude) * std::cos(latitude);
                v.Position.y = radius * std::sin(longtitude) * std::sin(latitude);
                v.Position.z = radius * std::cos(longtitude);
                mesh.Vertices.push_back(v);
            }
        }

        return mesh;
    }

    PrimitiveMesh PrimitiveMesh::GenerateQuad(float size)
    {
        const std::vector<Vertex> vertices
        {
            {{-size, size, 0.0f}, {0.0f, 1.0f}},
            {{size, size, 0.0f}, {1.0f, 1.0f}},
            {{size, -size, 0.0f}, {1.0f, 0.0f}},
            {{-size, -size, 0.0f}, {0.0f, 0.0f}},
        };

        const std::vector<uint32_t> indices
        {
            0, 1, 2, 0, 2, 3
        };

        return { vertices, indices };
    }

    PrimitiveMesh PrimitiveMesh::BasicSphere = PrimitiveMesh::GenerateSphere(1.0f, 16, 16);
    PrimitiveMesh PrimitiveMesh::BasicQuad = PrimitiveMesh::GenerateQuad(1.0f);
}
