#pragma once
#include "Macros.h"
#include <cstdint>

namespace Hydro
{
    struct HYDRO_API GraphicsSettings
    {
        using SwapchainBufferType = enum : uint32_t
        {
            DoubleBuffering = 2,
            TripleBuffering = 3
        };
        
        SwapchainBufferType BufferType;
        static GraphicsSettings DefaultSettings;
    };
}
