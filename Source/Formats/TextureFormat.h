#pragma once
#include "Core/Flags.h"

namespace Hydro
{
    enum HTexFlagBits : uint32_t
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
        uint32_t    Offset;
        uint32_t    Size;
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
        uint32_t Offset;
        uint32_t Size;
        HTexPixelFormatType Format;
    };
    
    struct HTexFile
    {
        HTexHeader Header;
    };

    
}
