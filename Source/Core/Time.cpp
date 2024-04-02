#include "HydroPCH.h"
#include "Time.h"
#include "GLFW/glfw3.h"

namespace Hydro
{
    float Time::GetTime()
    {
        return (float)glfwGetTime();
    }
}
