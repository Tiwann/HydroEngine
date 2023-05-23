#include "HydroPCH.h"
#include "Image.h"
#include "Assertion.h"
#include "ImageFormat.h"
#include "stb/stb_image.h"

namespace Hydro
{
    Image::Image(): m_Pixels(nullptr)
    {}

    Image::Image(const std::filesystem::path& filepath): m_Format(ImageFormat::RGBA8), m_Pixels(nullptr)
    {
        m_Pixels = stbi_load(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
    }

    Image::Image(const std::filesystem::path& filepath, ImageFormat format): m_Format(format), m_Pixels(nullptr)
    {

        switch (m_Format)
        {
        case ImageFormat::RGB8:
            m_Pixels = stbi_load(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 3);
            break;

        case ImageFormat::RGBA8:
            m_Pixels = stbi_load(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;

        case ImageFormat::RGB16:
            m_Pixels = stbi_load_16(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 3);
            break;

        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;

        case ImageFormat::RGB32:
        case ImageFormat::RGBA32:
            HYDRO_ASSERT(false, "RGB32 - RGBA32 not yet supported!");
            break;

        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf(filepath.string().c_str(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;
        }
    }

    Image::Image(const Buffer<uint8_t>& buffer) : m_Pixels(nullptr)
    {
        m_Pixels = stbi_load_from_memory(buffer.GetData(), (int)buffer.Count(), (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
    }

    Image::Image(const uint8_t* buffer, size_t size) : m_Pixels(nullptr)
    {
        m_Pixels = stbi_load_from_memory(buffer, (int)size, (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
    }

    Image::Image(const uint8_t* buffer, size_t size, ImageFormat format) : m_Format(format)
    {
        switch (m_Format)
        {
        case ImageFormat::RGB8:
            m_Pixels = stbi_load_from_memory(buffer, (int)size, (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 3);
            break;

        case ImageFormat::RGBA8:
            m_Pixels = stbi_load_from_memory(buffer, (int)size, (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;

        case ImageFormat::RGB16:
            m_Pixels = stbi_load_16_from_memory(buffer, (int)size, (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 3);
            break;

        case ImageFormat::RGBA16:
            m_Pixels = stbi_load_16_from_memory(buffer, (int)size, (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
            break;

        case ImageFormat::RGB32:
        case ImageFormat::RGBA32:
            HYDRO_ASSERT(false, "RGB32 - RGBA32 not yet supported!");
            break;

        case ImageFormat::RGBA32F:
            m_Pixels = stbi_loadf_from_memory(buffer, (int)size, (int32_t*)&m_Width, (int32_t*)&m_Height, nullptr, 4);
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

    const void* Image::GetData() const
    {
        return m_Pixels;
    }

    void* Image::GetData()
    {
        return m_Pixels;
    }
}


