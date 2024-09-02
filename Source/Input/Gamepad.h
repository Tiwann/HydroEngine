#pragma once
#include "Core/Containers/StringView.h"
#include "GamepadButton.h"
#include "InputState.h"
#include "Core/Containers/Map.h"
#include <GLFW/glfw3.h>


namespace Hydro
{
    class Gamepad
    {
    public:
        using ButtonStateMap = Map<GamepadButton, InputState>;
        Gamepad() = default;
        ~Gamepad()
        {
            m_ButtonsStates.Clear();
        }
        
        Gamepad(const Gamepad& other) = default;
        Gamepad(Gamepad&& other) noexcept;
        Gamepad& operator=(const Gamepad& other);
        Gamepad& operator=(Gamepad&& other) noexcept;

        void Initialize(u32 ID, const StringView& Name);
        bool GetButtonDown(GamepadButton Button);
        bool GetButton(GamepadButton Button);
        bool GetButtonUp(GamepadButton Button);

        u32 GetID() const;
        
        ButtonStateMap& GetButtonsStates();
        const StringView& GetName() const;
    private:
        u32 m_ID;
        StringView m_Name;
        ButtonStateMap m_ButtonsStates;
    };
}
