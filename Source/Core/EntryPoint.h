#pragma once
#include "Containers/DynamicArray.h"
#include "Containers/String.h"

#define HYDRO_DEFINE_APPLICATION_CLASS(ApplicationClass) Hydro::Application* Hydro::CreateApplication(const Hydro::Array<const char*>& Arguments) \
    { \
        static_assert(std::is_base_of_v<Application, ApplicationClass>, #ApplicationClass" isn't derived from Application");\
        return new (ApplicationClass)(Arguments); \
    } \

namespace Hydro
{
    extern class Application* CreateApplication(const Array<const char*>& Arguments);
    inline bool g_ApplicationRunning = true;
    int Main(int Argc, char** Argv);
}

