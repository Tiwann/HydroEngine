#pragma once
#include "Core/FrameBuffer.h"

namespace Hydro
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer();
        ~OpenGLFrameBuffer() override;
        
        void Bind() override;
        void Unbind() override;
        void AttachTexture(const Ref<Texture2D>& Texture, FrameBufferAttachment Attachment) override;
        void DetachTexture() override;
        bool Validate() override;


        static uint32_t GetOpenGLAttachment(FrameBufferAttachment Attachment);

    protected:
        uint32_t m_Handle;
    };
}
