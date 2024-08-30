#include "Gamepad.h"

namespace Hydro
{
    void Gamepad::Initialize(const uint32_t ID, const String& Name)
    {
        m_ID = ID;
        m_Name = Name;
    }

    bool Gamepad::GetButtonDown(GamepadButton Button)
    {
        return false;
    }

    bool Gamepad::GetButton(GamepadButton Button)
    {
        return false;
    }

    bool Gamepad::GetButtonUp(GamepadButton Button)
    {
        return false;
    }

    uint32_t Gamepad::GetID() const
    {
        return m_ID;
    }
}
