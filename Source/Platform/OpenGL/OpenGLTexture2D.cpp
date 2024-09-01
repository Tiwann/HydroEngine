#include "OpenGLTexture2D.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Core/Memory.h"
#include <glad/gl.h>

namespace Hydro
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& Name, uint32 Width, uint32 Height, const TextureParams& Params, uint32 Slot) : Texture2D(Name, Width, Height, Params, Slot)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);
        glActiveTexture(GL_TEXTURE0 + Slot);
        glBindTexture(GL_TEXTURE_2D, m_Handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetTextureFilter(m_Params.Filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetTextureFilter(m_Params.Filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetTextureWrap(m_Params.Wrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetTextureWrap(m_Params.Wrap));

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_Width, (GLsizei)m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Handle);
    }

    void OpenGLTexture2D::SetTextureParameters(const TextureParams& Params)
    {
        Bind();
        m_Params = Params;
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetTextureFilter(m_Params.Filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetTextureFilter(m_Params.Filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetTextureWrap(m_Params.Wrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetTextureWrap(m_Params.Wrap));
        Unbind();
    }

    void OpenGLTexture2D::SetData(uint8* Data, uint32 Width, uint32 Height, ImageFormat Format)
    {
        Bind();
        m_Width = Width;
        m_Height = Height;
        m_Format = Format;
        const GLenum Type = FormatToType(m_Format);
        const GLenum Fmt = FormatToOpenGLFormat(m_Format);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_Width, (GLsizei)m_Height, 0, Fmt, Type, Data);
        Unbind();
    }


    void OpenGLTexture2D::SetData(const Ref<Image>& Image)
    {
        Bind();
        m_Width = Image->GetWidth();
        m_Height = Image->GetHeight();
        m_Format = Image->GetFormat();
        const uint32 Type = FormatToType(m_Format);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_Width, (GLsizei)m_Height, 0, GL_RGBA, Type, Image->GetData());
        Unbind();
        HYDRO_LOG(Texture2D, Verbosity::Info, "Texture \"{}\": Data was set. Width: {}. Height: {}. Format: {}. Size: {}.", m_Name, m_Width, m_Height, FormatToString(m_Format), File::BytesToString(Image->GetSize()));
    }

    Ref<Image> OpenGLTexture2D::GetImage() const
    {
        Bind();
        size_t Size = 0;
        switch (m_Format)
        {
            case ImageFormat::RGBA8: Size = m_Width * m_Height * 4; break;
            case ImageFormat::RGBA16: Size = m_Width * m_Height * 4 * 2; break;
            case ImageFormat::RGBA32F: Size = m_Width * m_Height * 4 * 4; break;
        }
        uint8* Data = (uint8*)HYDRO_MALLOC(Size);
        glGetTextureImage(m_Handle, 0, GL_RGBA, FormatToType(m_Format), (GLsizei)Size, Data);
        Ref<Image> ImageData = CreateRef<Image>(m_Width, m_Height, m_Format, Data);
        HYDRO_FREE(Data);
        Unbind();
        return ImageData;
    }


    void OpenGLTexture2D::Bind() const
    {
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_Handle);
    }

    void OpenGLTexture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uintptr_t OpenGLTexture2D::GetHandle() const
    {
        return m_Handle;
    }

    uint32 OpenGLTexture2D::FormatToType(ImageFormat Format) const
    {
        switch (Format) {
        case ImageFormat::RGBA8: return GL_UNSIGNED_BYTE;
        case ImageFormat::RGBA16: return GL_UNSIGNED_SHORT;
        case ImageFormat::RGBA32F: return GL_FLOAT;
        }
        return 0;
    }

    GLint OpenGLTexture2D::GetTextureWrap(TextureWrap Wrap)
    {
        switch (Wrap) {
        case TextureWrap::Clamp: return GL_CLAMP_TO_EDGE;
        case TextureWrap::Repeat: return GL_REPEAT;
        case TextureWrap::Mirror: return GL_MIRRORED_REPEAT;
        }
        return 0;
    }

    GLint OpenGLTexture2D::GetTextureFilter(TextureFilter Filter)
    {
        switch (Filter)
        {
        case TextureFilter::Nearest: return GL_NEAREST;
        case TextureFilter::Linear: return GL_LINEAR;
        }
        return 0;
    }

    uint32 OpenGLTexture2D::FormatToOpenGLFormat(ImageFormat Format) const
    {
        switch (Format) {
        case ImageFormat::RGBA8: return GL_RGBA;
        case ImageFormat::RGBA16: return GL_RGBA;
        case ImageFormat::RGBA32F: return GL_RGBA;
        }
        return 0;
    }
}
