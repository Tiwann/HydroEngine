#pragma once
#include "Application.h"


#define HYDRO_DEFINE_APPLICATION_CLASS(ApplicationClass) Application* Hydro::CreateApplication() \
    { \
    return new ApplicationClass(); \
    } \

namespace Hydro
{
    extern Application* CreateApplication();
    inline bool g_ApplicationRunning = true;
    int Main(int argc, char** argv);
}

