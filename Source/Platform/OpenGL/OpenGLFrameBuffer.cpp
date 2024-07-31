#include "HydroPCH.h"
#include "OpenGLFrameBuffer.h"
#include <glad/gl.h>

#include "OpenGLTexture2D.h"

namespace Hydro
{
    OpenGLFrameBuffer::OpenGLFrameBuffer()
    {
        glCreateFramebuffers(1, &m_Handle);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_Handle);
    }

    void OpenGLFrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
    }

    void OpenGLFrameBuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::AttachTexture(const Ref<Texture2D>& Texture, FrameBufferAttachment Attachment)
    {
        m_AttachedTexture = Texture;
        m_Attachment = Attachment;
        uint32_t BufferAttachment = GetOpenGLAttachment(m_Attachment);
        Ref<OpenGLTexture2D> OpenGLTexture = Cast<OpenGLTexture2D>(Texture);
        glFramebufferTexture2D(GL_FRAMEBUFFER, BufferAttachment, GL_TEXTURE_2D, (GLint)OpenGLTexture->GetHandle(), 0); 
    }

    void OpenGLFrameBuffer::DetachTexture()
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GetOpenGLAttachment(m_Attachment), GL_TEXTURE_2D, 0, 0);
    }

    uint32_t OpenGLFrameBuffer::GetOpenGLAttachment(FrameBufferAttachment Attachment)
    {
        switch (Attachment)
        {
        case FrameBufferAttachment::Color:
            return GL_COLOR_ATTACHMENT0;
        case FrameBufferAttachment::Depth:
            return GL_DEPTH_ATTACHMENT;
        case FrameBufferAttachment::Stencil:
            return GL_STENCIL_ATTACHMENT;
        }
        return UINT_MAX;
    }

    bool OpenGLFrameBuffer::Validate()
    {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }
}
