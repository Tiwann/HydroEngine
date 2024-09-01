#include "Gamepad.h"

namespace Hydro
{
    Gamepad::Gamepad(Gamepad&& other) noexcept : m_ID(other.m_ID),
                                                 m_Name(other.m_Name),
                                                 m_ButtonsStates(std::move(other.m_ButtonsStates))
    {
    }

    Gamepad& Gamepad::operator=(const Gamepad& other)
    {
        if (this == &other)
            return *this;
        
        m_ID = other.m_ID;
        m_Name = other.m_Name;
        m_ButtonsStates = other.m_ButtonsStates;
        return *this;
    }

    Gamepad& Gamepad::operator=(Gamepad&& other) noexcept
    {
        if (this == &other)
            return *this;
        m_ID = other.m_ID;
        m_Name = other.m_Name;
        m_ButtonsStates = std::move(other.m_ButtonsStates);
        return *this;
    }

    void Gamepad::Initialize(const uint32_t ID, const StringView& Name)
    {
        m_ButtonsStates.Clear(); 
        m_ID = ID;
        m_Name = Name;
    }

    bool Gamepad::GetButtonDown(GamepadButton Button)
    {
        return m_ButtonsStates[Button] == InputState::Pressed;
    }

    bool Gamepad::GetButton(GamepadButton Button)
    {
        return false;
    }

    bool Gamepad::GetButtonUp(GamepadButton Button)
    {
        return m_ButtonsStates[Button] == InputState::Released;
    }

    uint32_t Gamepad::GetID() const
    {
        return m_ID;
    }

    Gamepad::ButtonStateMap& Gamepad::GetButtonsStates()
    {
        return m_ButtonsStates;
    }

    const StringView& Gamepad::GetName() const
    {
        return m_Name;
    }
}
