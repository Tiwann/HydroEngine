#include "HydroPCH.h"
#include "Image.h"

#include <stb/stb_image.h>

namespace Hydro
{
    Image::Image(const std::filesystem::path& filepath, ImageFormat format): m_Format(format), m_Pixels(nullptr)
    {
        stbi_set_flip_vertically_on_load(true);
        switch (m_Format)
        {
        case ImageFormat::RGBA8:
            m_Pixels = stbi_load(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        }
    }

    Image::Image(const Buffer<uint8_t>& buffer, ImageFormat format) : m_Format(format), m_Pixels(nullptr)
    {
        stbi_set_flip_vertically_on_load(true);
        switch (m_Format)
        {
        case ImageFormat::RGBA8:
            m_Pixels = stbi_load_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        }
    }

    Image::Image(const BufferView<uint8_t>& buffer, ImageFormat format) : m_Format(format), m_Pixels(nullptr)
    {
        stbi_set_flip_vertically_on_load(true);
        switch (m_Format)
        {
        case ImageFormat::RGBA8:
            m_Pixels = stbi_load_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        }
    }
    
    Image::~Image()
    {
        stbi_image_free(m_Pixels);
    }

    uint32_t Image::GetWidth() const
    {
        return m_Width;
    }

    uint32_t Image::GetHeight() const
    {
        return m_Height;
    }

    size_t Image::GetSize() const
    {
        return m_Width * m_Height * 4 * (((m_Format == RGBA8) ? 1 : (m_Format == RGBA16)) ? 2 : 4);
    }

    const void* Image::GetData() const
    {
        return m_Pixels;
    }

    void* Image::GetData()
    {
        return m_Pixels;
    }

    bool Image::Valid() const
    {
        return m_Pixels && m_Width && m_Height;
    }

    ImageFormat Image::GetFormat() const
    {
        return m_Format;
    }

    Ref<Image> Image::Create(const Path& Filepath, ImageFormat Format)
    {
        return CreateRef<Image>(Filepath, Format);
    }

    Ref<Image> Image::Create(const Buffer<uint8_t>& Buffer, ImageFormat Format)
    {
        return CreateRef<Image>(Buffer, Format);
    }
    
    Ref<Image> Image::Create(const BufferView<uint8_t>& BufferView, ImageFormat Format)
    {
        return CreateRef<Image>(BufferView, Format);
    }
}


