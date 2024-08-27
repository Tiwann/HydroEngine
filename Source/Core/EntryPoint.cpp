#include "EntryPoint.h"
#include "Application.h"

namespace Hydro
{
    int Main(const int Argc, const char** Argv)
    {
        while (g_ApplicationRunning)
        {
            g_Application = CreateApplication(Array<const char*>(Argv, Argc));
            g_Application->Run();
            delete g_Application;
        }
        return 0;
    }
}


#if defined(HYDRO_PLATFORM_WINDOWS) && defined(HYDRO_RELEASE)
INT APIENTRY WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
    return Hydro::Main(__argc, __argv);
}
#else
int main(const int argc, const char** argv)
{
    return Hydro::Main(argc, argv);
}
#endif

