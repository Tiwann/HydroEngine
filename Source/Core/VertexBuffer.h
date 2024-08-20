#pragma once
#include "Buffer.h"
#include "SharedPointer.h"
#include "Vertex.h"
#include "Containers/StaticArray.h"

namespace Hydro
{
    
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(Vertex* Data, size_t Count);
        virtual ~VertexBuffer() = default;

        static Ref<VertexBuffer> Create();
        static Ref<VertexBuffer> Create(Vertex* Data, size_t Count);

        virtual void SendData(Vertex* Data, size_t Count);

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

    protected:
        BufferView<Vertex> m_Data;
    };
}
