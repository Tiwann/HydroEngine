#pragma once
#include "Core/IndexBuffer.h"

namespace Hydro
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer();
        OpenGLIndexBuffer(uint32_t* Indices, size_t Count);
        
        ~OpenGLIndexBuffer() override;
        void Bind() override;
        void Unbind() override;
        void SendData(uint32_t* Indices, size_t Count) override;
        void SendData(const std::initializer_list<uint32_t>& List) override;
    private:
        uint32_t m_Handle;
    };
}
