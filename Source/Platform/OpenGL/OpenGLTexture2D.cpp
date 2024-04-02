#include "HydroPCH.h"
#include "OpenGLTexture2D.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Core/Memory.h"
#include <glad/gl.h>

namespace Hydro
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& Name, uint32_t Slot) : Texture2D(Name, Slot)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);
        glActiveTexture(GL_TEXTURE0 + Slot);
        glBindTexture(GL_TEXTURE_2D, m_Handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Handle);
    }
    
    void OpenGLTexture2D::SetImage(const Ref<Image>& Image)
    {
        Bind();
        m_Width = Image->GetWidth();
        m_Height = Image->GetHeight();
        m_Format = Image->GetFormat();
        const uint32_t Type = FormatToType(m_Format);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, Type, Image->GetData());
        HYDRO_LOG(Texture2D, Info, "Texture \"{}\": Data was set. Width: {}. Height: {}. Format: {}. Size: {}.", m_Name, m_Width, m_Height, FormatToString(m_Format), File::BytesToString(Image->GetSize()));
    }

    Ref<Image> OpenGLTexture2D::GetImage() const
    {
        Bind();
        size_t Size = 0;
        switch (m_Format)
        {
            case RGBA8: Size = m_Width * m_Height * 4; break;
            case RGBA16: Size = m_Width * m_Height * 4 * 2; break;
            case RGBA32F: Size = m_Width * m_Height * 4 * 4; break;
        }
        uint8_t* Data = (uint8_t*)HYDRO_MALLOC(Size);
        glGetTextureImage(m_Handle, 0, GL_RGBA, FormatToType(m_Format), (GLsizei)Size, Data);
        Ref<Image> ImageData = CreateRef<Image>(m_Width, m_Height, m_Format, Data);
        HYDRO_FREE(Data);
        return ImageData;
    }


    void OpenGLTexture2D::Bind() const
    {
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_Handle);
    }

    uint32_t OpenGLTexture2D::FormatToType(ImageFormat Format) const
    {
        switch (Format) {
        case RGBA8: return GL_UNSIGNED_BYTE;
        case RGBA16: return GL_UNSIGNED_SHORT;
        case RGBA32F: return GL_FLOAT;
        }
        return 0;
    }

    uint32_t OpenGLTexture2D::FormatToOpenGLFormat(ImageFormat Format) const
    {
        switch (Format) {
        case RGBA8: return GL_RGBA8;
        case RGBA16: return GL_RGBA16;
        case RGBA32F: return GL_RGBA32F;
        }
        return 0;
    }
}
