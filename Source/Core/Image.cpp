#include "Image.h"

#include <stb/stb_image.h>

namespace Hydro
{
    Image::Image(uint32_t Width, uint32_t Height, ImageFormat Format, const void* Pixels): m_Width(Width), m_Height(Height), m_Format(Format)
    {
        const size_t Size = m_Format == ImageFormat::RGBA8 ? 1 : m_Format == ImageFormat::RGBA16 ? 2 : 4;
        m_Pixels = malloc((size_t)(m_Width * m_Height) * 4 * Size);
        std::copy_n((const uint8_t*)Pixels, Size, (uint8_t*)m_Pixels);
    }

    Image::Image(const std::filesystem::path& Filepath, ImageFormat Fmt): m_Format(Fmt), m_Pixels(nullptr)
    {
        stbi_set_flip_vertically_on_load(true);
        switch (m_Format)
        {
        case ImageFormat::RGBA8:
            m_Pixels = stbi_load(Filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16(Filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf(Filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        }
    }

    Image::Image(const Buffer<uint8_t>& Buffer, ImageFormat Fmt) : m_Format(Fmt), m_Pixels(nullptr)
    {
        stbi_set_flip_vertically_on_load(true);
        switch (m_Format)
        {
        case ImageFormat::RGBA8:
            m_Pixels = stbi_load_from_memory(Buffer.GetData(), (int)Buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16_from_memory(Buffer.GetData(), (int)Buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf_from_memory(Buffer.GetData(), (int)Buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        }
    }

    Image::Image(const BufferView<uint8_t>& Buffer, ImageFormat Fmt) : m_Format(Fmt), m_Pixels(nullptr)
    {
        stbi_set_flip_vertically_on_load(true);
        switch (m_Format)
        {
        case ImageFormat::RGBA8:
            m_Pixels = stbi_load_from_memory(Buffer.GetData(), (int)Buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16_from_memory(Buffer.GetData(), (int)Buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        
        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf_from_memory(Buffer.GetData(), (int)Buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
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
        return (size_t)(m_Width * m_Height) * 4 * (((m_Format == ImageFormat::RGBA8) ? 1 : (m_Format == ImageFormat::RGBA16)) ? 2 : 4);
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


