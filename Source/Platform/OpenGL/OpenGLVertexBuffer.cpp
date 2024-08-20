#include "HydroPCH.h"
#include "OpenGLVertexBuffer.h"

#include <glad/gl.h>

namespace Hydro
{
    OpenGLVertexBuffer::OpenGLVertexBuffer()
    {
        glCreateBuffers(1, &m_Handle);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(Vertex* Data, size_t Count)
    : VertexBuffer(Data, Count)
    {
        glCreateBuffers(1, &m_Handle);
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)m_Data.Size(), m_Data.GetData(), GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_Handle);
    }

    void OpenGLVertexBuffer::SendData(Vertex* Data, size_t Count)
    {
        VertexBuffer::SendData(Data, Count);
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)m_Data.Size(), m_Data.GetData(), GL_STATIC_DRAW);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
