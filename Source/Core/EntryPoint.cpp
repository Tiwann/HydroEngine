#include "HydroPCH.h"
#include "EntryPoint.h"

namespace Hydro
{
    int Main(int argc, char** argv)
    {
        while (g_ApplicationRunning)
        {
            Application* application = CreateApplication();
            application->Run();
            delete application;
        }
        return 0;
    }
}

int main(int argc, char** argv)
{
    return Hydro::Main(argc, argv);
}

