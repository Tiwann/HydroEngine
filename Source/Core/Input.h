#pragma once
#include "KeyCodes.h"
#include "Macros.h"

namespace Hydro
{
    struct HYDRO_API KeyState
    {
        bool Pressed;
        bool Hold;
        bool Up;
    };
    
    class HYDRO_API Input
    {
    public:
        static bool GetKeyDown(KeyCode KeyCode);
        static bool GetKey(KeyCode KeyCode);
        static bool GetKeyUp(KeyCode KeyCode);
        static void Reset();

    private:
        friend class Application;
        static bool m_Keys[HYDRO_KEY_TOTAL];
        static KeyState m_KeyStates[HYDRO_KEY_TOTAL];
    };
}
