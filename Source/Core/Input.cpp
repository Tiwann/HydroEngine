#include "HydroPCH.h"
#include "Input.h"

namespace Hydro
{
    bool Input::m_Keys[HYDRO_KEY_TOTAL] = {};
    KeyState Input::m_KeyStates[HYDRO_KEY_TOTAL]{};

    bool Input::GetKeyDown(KeyCode KeyCode)
    {
        return false;
    }

    bool Input::GetKey(KeyCode KeyCode)
    {
        return m_KeyStates[KeyCode].Pressed;
    }

    bool Input::GetKeyUp(KeyCode KeyCode)
    {
        return m_KeyStates[KeyCode].Up;
    }

    void Input::Reset()
    {
        for(uint32_t i = 0; i < HYDRO_KEY_TOTAL; i++)
        {
            Input::m_KeyStates[i].Pressed = false;
            Input::m_KeyStates[i].Hold = false;
            Input::m_KeyStates[i].Up = false;
        }
    }
}
