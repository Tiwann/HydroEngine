#pragma once
#include <type_traits>


#define HYDRO_DEFINE_APPLICATION_CLASS(ApplicationClass) Hydro::Application* Hydro::CreateApplication() \
    { \
    static_assert(std::is_base_of_v<Application, ApplicationClass>, #ApplicationClass" isn't derived from Application");\
    return new (ApplicationClass)(); \
    } \

namespace Hydro
{
    extern class Application* CreateApplication();
    inline bool g_ApplicationRunning = true;
    int Main(int argc, char** argv);
}

