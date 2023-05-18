#pragma once
#include "HydroPCH.h"
#include "String.h"

namespace Hydro
{
    enum class SwapchainBufferType : uint32_t
    {
        DoubleBuffering = 2,
        TripleBuffering = 3
    };
    
    struct HYDRO_API ApplicationSpecs
    {
        String AppName{};
        uint32_t WindowWidth{};
        uint32_t WindowHeight{};
        bool StartFullscreen = false;
        bool WindowResizable = false;
        bool ShowGraphicsAPIName = false;
        bool ShowConfiguration = false;
        bool ShowOSName = false;
        bool ShowDeltaTime = false;
        bool ShowFPS = false;
        float WindowTitleUpdateTime = 0.0f;
        SwapchainBufferType SwapchainBuffer = SwapchainBufferType::DoubleBuffering;
    };
}
