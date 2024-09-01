#pragma once
#include "Buffer.h"
#include "Types.h"
#include "SharedPointer.h"

namespace Hydro
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        IndexBuffer(uint32* Indices, size_t Count);
        virtual ~IndexBuffer() = default;
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SendData(uint32* Indices, size_t Count);
        virtual void SendData(const std::initializer_list<uint32>& List);
        size_t Count() const;

        static Ref<IndexBuffer> Create();
        static Ref<IndexBuffer> Create(uint32* Indices, size_t Count);
        static Ref<IndexBuffer> Create(const std::initializer_list<uint32>& List);
    protected:
        BufferView<uint32> m_Data;
    };
}
