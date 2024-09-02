#include "FrameBuffer.h"
#include "Macros.h"
#include "Texture2D.h"
#include "Platform/PlatformFrameBuffer.h"


namespace Hydro
{
    FrameBuffer::FrameBuffer()
    {
    }

    FrameBuffer::FrameBuffer(FrameBufferAttachment Attachement) : m_Attachment(Attachement)
    {
    }

    FrameBuffer::~FrameBuffer()
    {
    }

    void FrameBuffer::Resize(Vector2 NewSize)
    {
        Bind();
        if(m_AttachedTexture)
        {
            m_AttachedTexture->SetData(nullptr, (u32)NewSize.x, (u32)NewSize.y, ImageFormat::RGBA8);
        }
        Unbind();
    }

    Ref<Texture2D> FrameBuffer::GetAttachedTexture() const
    {
        return m_AttachedTexture;
    }

    FrameBufferAttachment FrameBuffer::GetAttachment() const
    {
        return m_Attachment;
    }

    Ref<FrameBuffer> FrameBuffer::Create()
    {
        HYDRO_RHI_PLATFORM_RETURN(FrameBuffer);
    }

    Ref<FrameBuffer> FrameBuffer::Create(FrameBufferAttachment Attachement)
    {
        HYDRO_RHI_PLATFORM_RETURN(FrameBuffer, Attachement);
    }
}
