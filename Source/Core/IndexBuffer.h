#pragma once
#include "Buffer.h"
#include "SharedPointer.h"

namespace Hydro
{
    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* Indices, size_t Count);
        virtual ~IndexBuffer() = default;
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SendData(uint32_t* Indices, size_t Count) = 0;
        size_t Count() const;

        static Ref<IndexBuffer> Create(uint32_t* Indices, size_t Count);
        static Ref<IndexBuffer> Create(const std::initializer_list<uint32_t>& List);
    protected:
        BufferView<uint32_t> m_Data;
    };
}
