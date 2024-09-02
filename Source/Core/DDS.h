#pragma once
#include "Filesystem.h"
#include "Buffer.h"
#include "Flags.h"

namespace Hydro
{
    // From https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dds-header
    enum class DDSFlagsBits : u32
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
    
    enum class DDSCapsBits : u32
    {
        Complex = 0x8,
        MipMap = 0x400000,
        Texture = 0x1000
    };

    using DDSCapsFlags = Flags<DDSCapsBits>;
    
    enum class DDSCaps2Bits : u32
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
    
    enum class DDSPixelFormatBits : u32
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
        u32 Size;
        DDSPixelFormatFlags Flags;
        u32 FourCC;
        u32 RGBBitCount;
        u32 RBitMask;
        u32 GBitMask;
        u32 BBitMask;
        u32 ABitMask;
    };
    
    struct DDSHeader
    {
        u32           Size;
        DDSHeaderFlags     Flags;
        u32           Height;
        u32           Width;
        u32           PitchOrLinearSize;
        u32           Depth;
        u32           MipMapCount;
        u32           Reserved1[11];
        DDSPixelFormat     PixelFormat;
        DDSCapsFlags       Caps;
        DDSCaps2Flags      Caps2;
        u32           Padding[3];
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
