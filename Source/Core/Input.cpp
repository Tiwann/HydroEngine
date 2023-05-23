#include "HydroPCH.h"
#include "Input.h"

namespace Hydro
{
    bool Input::m_Keys[HYDRO_KEY_TOTAL] = {};

    bool Input::GetKey(KeyCode keycode)
    {
        return m_Keys[(uint32_t)keycode];
    }
}
