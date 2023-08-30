#pragma once
#include "Macros.h"

namespace Hydro
{
    class HYDRO_API Time
    {
    public:
        static float GetTime();

    private:
        static float m_Time;
        friend class Application;
    };
}
