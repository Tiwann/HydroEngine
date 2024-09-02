#pragma once
#include "Buffer.h"
#include "NumericTypes.h"
#include "SharedPointer.h"

namespace Hydro
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        IndexBuffer(u32* Indices, size_t Count);
        virtual ~IndexBuffer() = default;
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SendData(u32* Indices, size_t Count);
        virtual void SendData(const std::initializer_list<u32>& List);
        size_t Count() const;

        static Ref<IndexBuffer> Create();
        static Ref<IndexBuffer> Create(u32* Indices, size_t Count);
        static Ref<IndexBuffer> Create(const std::initializer_list<u32>& List);
    protected:
        BufferView<u32> m_Data;
    };
}
