#pragma once
#include "Core/Containers/String.h"
#include "GamepadButton.h"
#include "InputState.h"
#include "Core/Containers/Map.h"
#include <GLFW/glfw3.h>


namespace Hydro
{
    class Gamepad
    {
    public:
        Gamepad() = default;
        ~Gamepad() = default;
        
        void Initialize(const uint32_t ID, const String& Name);
        bool GetButtonDown(GamepadButton Button);
        bool GetButton(GamepadButton Button);
        bool GetButtonUp(GamepadButton Button);

        uint32_t GetID() const;

    private:
        uint32_t m_ID;
        String m_Name;
        Map<GamepadButton, InputState> m_State;
    };
}
