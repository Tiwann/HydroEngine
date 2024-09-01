#pragma once
#include "Core/FrameBuffer.h"
#include "Core/Types.h"

typedef uint32 GLenum;

namespace Hydro
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer();
        OpenGLFrameBuffer(FrameBufferAttachment Attachment);
        ~OpenGLFrameBuffer() override;

        void Destroy() override;
        void Bind() override;
        void Unbind() override;
        void AttachTexture(const Ref<Texture2D>& Texture, FrameBufferAttachment Attachment) override;
        void DetachTexture() override;
        bool Validate() override;


        static GLenum GetOpenGLAttachment(FrameBufferAttachment Attachment);

    protected:
        uint32 m_Handle;
    };
}
