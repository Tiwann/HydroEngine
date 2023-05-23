#pragma once
#include "String.h"
#include "GraphicsSettings.h"

namespace Hydro
{
    struct HYDRO_API ApplicationConfiguration
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
        GraphicsSettings GraphicsSettings;
    };
}
