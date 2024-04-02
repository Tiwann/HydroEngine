#pragma once
#include "GraphicsSettings.h"
#include <string>

namespace Hydro
{
    struct ApplicationConfiguration
    {
        std::string AppName{};
        uint32_t WindowWidth{0};
        uint32_t WindowHeight{0};
        bool StartFullscreen = false;
        bool WindowResizable = false;
        bool ShowGraphicsAPIName = false;
        bool ShowConfiguration = false;
        bool ShowOSName = false;
        bool ShowDeltaTime = false;
        bool ShowFPS = false;
        float WindowTitleUpdateTime = 0.0f;
        GraphicsSettings Graphics;
    };
}
