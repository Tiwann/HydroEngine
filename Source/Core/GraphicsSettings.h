#pragma once
#include <cstdint>

namespace Hydro
{
    struct GraphicsSettings
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
