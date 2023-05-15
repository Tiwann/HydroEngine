#pragma once
#include "Application.h"


namespace Hydro
{
    extern Application* CreateApplication();
    inline bool g_ApplicationRunning = true;
    int Main(int argc, char** argv);
}

