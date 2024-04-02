#pragma once
#include "KeyCodes.h"

namespace Hydro
{
    struct KeyState
    {
        bool IsPressed;
        bool IsHold;
        bool IsRelease;
        bool WasPressed;
    };
    
    class Input
    {
    public:
        friend class Application;
        static bool GetKeyDown(KeyCode KeyCode);
        static bool GetKey(KeyCode KeyCode);
        static bool GetKeyUp(KeyCode KeyCode);
        static std::string GetKeyName(KeyCode KeyCode);

        static KeyState GetState(KeyCode KeyCode);
    private:
        static KeyState States[TOTAL];
    };
}
