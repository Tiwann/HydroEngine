#include "OpenGLFrameBuffer.h"
#include <glad/gl.h>

#include "OpenGLTexture2D.h"

namespace Hydro
{
    OpenGLFrameBuffer::OpenGLFrameBuffer()
    {
        glCreateFramebuffers(1, &m_Handle);
    }

    OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferAttachment Attachment) : FrameBuffer(Attachment)
    {
        glCreateFramebuffers(1, &m_Handle);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

        TextureParams TexParams;
        TexParams.Filter = TextureFilter::Nearest;
        TexParams.Wrap = TextureWrap::Clamp;
        
        m_AttachedTexture = Texture2D::Create("OpenGLFrameBuffer", 0, 0, TexParams);
        m_AttachedTexture->SetData(nullptr, 0, 0, ImageFormat::RGBA8);
        GLenum BufferAttachment = GetOpenGLAttachment(m_Attachment);
        glFramebufferTexture2D(GL_FRAMEBUFFER, BufferAttachment, GL_TEXTURE_2D, (GLuint)m_AttachedTexture->GetHandle(), 0); 
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        Destroy();
    }

    void OpenGLFrameBuffer::Destroy()
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
        Bind();
        m_AttachedTexture = Texture;
        m_Attachment = Attachment;
        GLenum BufferAttachment = GetOpenGLAttachment(m_Attachment);
        glFramebufferTexture2D(GL_FRAMEBUFFER, BufferAttachment, GL_TEXTURE_2D, (GLint)Texture->GetHandle(), 0);
        Unbind();
    }

    void OpenGLFrameBuffer::DetachTexture()
    {
        Bind();
        m_AttachedTexture = nullptr;
        m_Attachment = FrameBufferAttachment::None;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GetOpenGLAttachment(m_Attachment), GL_TEXTURE_2D, 0, 0);
        Unbind();
    }

    GLenum OpenGLFrameBuffer::GetOpenGLAttachment(FrameBufferAttachment Attachment)
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
        Bind();
        GLenum Result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        Unbind();
        return Result == GL_FRAMEBUFFER_COMPLETE;
    }
}
