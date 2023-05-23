#pragma once
#include "KeyCodes.h"

namespace Hydro
{
    class HYDRO_API Input
    {
    public:
        static bool GetKey(KeyCode keycode);


    private:
        friend class Application;
        static bool m_Keys[HYDRO_KEY_MENU];
    };
}
