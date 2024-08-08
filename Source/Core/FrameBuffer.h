#pragma once
#include "SharedPointer.h"

namespace Hydro
{
    class Texture2D;
    
    enum class FrameBufferAttachment
    {
        None,
        Color,
        Depth,
        Stencil
    };
    
    class FrameBuffer
    {
    public:
        FrameBuffer();
        FrameBuffer(FrameBufferAttachment Attachement);
        virtual ~FrameBuffer();

        virtual void Destroy() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void AttachTexture(const Ref<Texture2D>& Texture, FrameBufferAttachment Attachment) = 0;
        virtual void DetachTexture() = 0;
        virtual bool Validate() = 0;

        Ref<Texture2D> GetAttachedTexture() const;
        FrameBufferAttachment GetAttachment() const;
        

        static Ref<FrameBuffer> Create();
        static Ref<FrameBuffer> Create(FrameBufferAttachment Attachement);
    protected:
        Ref<Texture2D> m_AttachedTexture;
        FrameBufferAttachment m_Attachment;
    };
}
