#include "HydroPCH.h"
#include "OpenGLIndexBuffer.h"

#include <glad/gl.h>

namespace Hydro
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, size_t Count)
        : IndexBuffer(Indices, Count)
    {
        glCreateBuffers(1, &m_Handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)m_Data.Size(), m_Data.GetData(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_Handle);
    }

    void OpenGLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
    }

    void OpenGLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::SendData(uint32_t* Indices, size_t Count)
    {
        m_Data = {Indices, Count};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)m_Data.Size(), m_Data.GetData(), GL_STATIC_DRAW);
    }
}
