#pragma once
#include "GraphicsSettings.h"
#include "Filesystem.h"
#include <string>

namespace Hydro
{
    struct ApplicationConfiguration
    {
        std::string AppName{};
        Path IconPath{};
        u32 WindowWidth{0};
        u32 WindowHeight{0};
        bool StartFullscreen = false;
        bool WindowResizable = false;
        bool ShowGraphicsAPIName = false;
        bool ShowConfiguration = false;
        bool ShowOSName = false;
        bool ShowDeltaTime = false;
        bool ShowFPS = false;
        f32 WindowTitleUpdateTime = 0.0f;
        bool WithEditor = false;
        GraphicsSettings Graphics;

        static ApplicationConfiguration DefaultRuntime;
    };
}
