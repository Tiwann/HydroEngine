#pragma once

namespace Hydro
{
    struct HYDRO_API GraphicsSettings
    {
        using SwapchainBufferType = enum class SwapchainBufferType : uint32_t
        {
            DoubleBuffering = 2,
            TripleBuffering = 3
        };
        
        SwapchainBufferType BufferType;
    };
}
