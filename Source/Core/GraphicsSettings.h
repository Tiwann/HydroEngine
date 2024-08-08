#pragma once
#include <cstdint>

namespace Hydro
{
    struct GraphicsSettings
    {
        enum class SwapchainBufferType
        {
            DoubleBuffering = 2,
            TripleBuffering = 3
        };
        
        SwapchainBufferType BufferType = SwapchainBufferType::TripleBuffering;
        static GraphicsSettings DefaultSettings;
    };
}
