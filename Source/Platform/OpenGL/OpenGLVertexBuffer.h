#pragma once
#include "Core/VertexBuffer.h"


namespace Hydro
{
    struct Vertex;
    
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(Vertex* Data, size_t Count);
        ~OpenGLVertexBuffer() override;
        
        void SendData() override;
        void Bind() const override;
        void Unbind() const override;

    private:
        uint32_t m_Handle;
    };
}
