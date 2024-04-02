#pragma once
#include "Buffer.h"
#include "SharedPointer.h"
#include "Vertex.h"

namespace Hydro
{
    
    class VertexBuffer
    {
    public:
        VertexBuffer(Vertex* Data, size_t Count);
        virtual ~VertexBuffer() = default;
        static Ref<VertexBuffer> Create(Vertex* Data, size_t Count);

        virtual void SendData() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        BufferView<Vertex> m_Data;
    };
}
