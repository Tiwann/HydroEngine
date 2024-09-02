#pragma once
#include "Core/Flags.h"

namespace Hydro
{
    enum HTexFlagBits : u32
    {
        None = 0,
        HYDRO_FLAG_BIT(PixelFormat, 0),
        HYDRO_FLAG_BIT(Compression, 1),
        HYDRO_FLAG_BIT(Data, 2)
    };

    using HTexFlags = Flags<HTexFlagBits>;
    
    struct HTexHeader
    {
        char        Magic[4]{ 'H', 'T', 'E', 'X' };
        u32    Offset;
        u32    Size;
        HTexFlags   Flags;
    };

    enum HTexPixelFormatType
    {
        RGBAU8,
        RGBAU16,
        RGBAU32,
        RGBAF32,
        RGB
    };

    struct HTexPixelFormat
    {
        char Magic[4]{ 'P', 'F', 'M', 'T'};
        u32 Offset;
        u32 Size;
        HTexPixelFormatType Format;
    };
    
    struct HTexFile
    {
        HTexHeader Header;
    };

    
}
