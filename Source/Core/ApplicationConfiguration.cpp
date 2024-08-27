#include "ApplicationConfiguration.h"

namespace Hydro
{
    ApplicationConfiguration ApplicationConfiguration::DefaultRuntime = {
        .WindowWidth = 800,
        .WindowHeight = 600,
        .WindowResizable = false,
        .ShowGraphicsAPIName = true,
        .ShowConfiguration = false,
        .ShowOSName = true,
        .ShowDeltaTime = false,
        .ShowFPS = true,
        .WindowTitleUpdateTime = 0.0f,
        .WithEditor = false
    };
}