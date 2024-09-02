#include "Time.h"
#include <GLFW/glfw3.h>

namespace Hydro
{
    f32 Time::GetTime()
    {
        return (f32)glfwGetTime();
    }
}
