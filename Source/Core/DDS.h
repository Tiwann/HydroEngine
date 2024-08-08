#pragma once
#include "Filesystem.h"
#include "Buffer.h"
#include "Flags.h"

namespace Hydro
{
    // From https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dds-header
    enum class DDSFlagsBits : uint32_t
    {
        Caps = 0x1,
        Width = 0x2,
        Height = 0x4,
        Picth = 0x8,
        PixelFormat = 0x1000,
        MipMapCount = 0x20000,
        LinearSize = 0x80000,
        Depth = 0x800000
    };

    using DDSHeaderFlags = Flags<DDSFlagsBits>;
    
    enum class DDSCapsBits : uint32_t
    {
        Complex = 0x8,
        MipMap = 0x400000,
        Texture = 0x1000
    };

    using DDSCapsFlags = Flags<DDSCapsBits>;
    
    enum class DDSCaps2Bits : uint32_t
    {
        Cubemap = 0x200,
        CubemapPosX = 0x400,
        CubemapNegX = 0x800,
        CubemapPosY = 0x1000,
        CubemapNegY = 0x2000,
        CubemapPosZ = 0x4000,
        CubemapNegZ = 0x8000,
        Volume = 0x200000,
    };

    using DDSCaps2Flags = Flags<DDSCaps2Bits>;
    
    enum class DDSPixelFormatBits : uint32_t
    {
        AlphaPixels = 0x1,
        Alpha = 0x2,
        FourCC = 0x4,
        RGB = 0x40,
        YUV = 0x200,
        Luminance = 0x20000
    };

    using DDSPixelFormatFlags = Flags<DDSPixelFormatBits>;
    
    struct DDSPixelFormat
    {
        uint32_t Size;
        DDSPixelFormatFlags Flags;
        uint32_t FourCC;
        uint32_t RGBBitCount;
        uint32_t RBitMask;
        uint32_t GBitMask;
        uint32_t BBitMask;
        uint32_t ABitMask;
    };
    
    struct DDSHeader
    {
        uint32_t           Size;
        DDSHeaderFlags     Flags;
        uint32_t           Height;
        uint32_t           Width;
        uint32_t           PitchOrLinearSize;
        uint32_t           Depth;
        uint32_t           MipMapCount;
        uint32_t           Reserved1[11];
        DDSPixelFormat     PixelFormat;
        DDSCapsFlags       Caps;
        DDSCaps2Flags      Caps2;
        uint32_t           Padding[3];
    };

    // From https://www.youtube.com/watch?v=1iq89Qu6YTU&t=1820s
    struct DDSFile
    {
        char      Magic[4];
        DDSHeader Header;
        char* Data() { return (char*)this + sizeof(Magic) + sizeof(Header); }

        static DDSFile* LoadDDS(const Path& Path, size_t& Size)
        {
            Buffer DDSData = File::ReadToBuffer(Path);
            Size = DDSData.Size();
            return (DDSFile*)DDSData.GetData();
        }
    };
}
