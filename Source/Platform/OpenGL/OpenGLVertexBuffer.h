#pragma once
#include "Core/VertexBuffer.h"


namespace Hydro
{
    struct Vertex;
    
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer();
        OpenGLVertexBuffer(Vertex* Data, size_t Count);
        ~OpenGLVertexBuffer() override;
        
        void SendData(Vertex* Data, size_t Count) override;
        void Bind() const override;
        void Unbind() const override;

    private:
        u32 m_Handle;
    };
}
