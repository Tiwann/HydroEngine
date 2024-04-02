#pragma once
#include "Buffer.h"
#include "Vertex.h"

namespace Hydro
{
    struct Submesh
    {
        Buffer<Vertex> Vertices;
        Buffer<uint32_t> Indices;
    };
    
    class Mesh
    {
    public:
        void SetData(const BufferView<Vertex>& Vertices, const BufferView<uint32_t>& Indices);
    private:
        std::vector<Submesh> m_Meshes;
    };

    
}
