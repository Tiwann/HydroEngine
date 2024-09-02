#pragma once
#include "Core/IndexBuffer.h"

namespace Hydro
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer();
        OpenGLIndexBuffer(u32* Indices, size_t Count);
        
        ~OpenGLIndexBuffer() override;
        void Bind() override;
        void Unbind() override;
        void SendData(u32* Indices, size_t Count) override;
        void SendData(const std::initializer_list<u32>& List) override;
    private:
        u32 m_Handle;
    };
}
