#include "Input.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Math/Vector2.h"
#include <GLFW/glfw3.h>

namespace Hydro
{
    bool Input::GetKeyDown(KeyCode KeyCode)
    {
        return s_KeyStates[KeyCode] == InputState::Pressed;
    }

    bool Input::GetKey(KeyCode KeyCode)
    {
        const Ref<Window>& Window = g_Application->GetWindow();
        const int State = glfwGetKey(Window->GetNativeWindow(), (int)KeyCode);
        return State == GLFW_PRESS;
    }

    bool Input::GetKeyUp(KeyCode KeyCode)
    {
        return s_KeyStates[KeyCode] == InputState::Released;
    }

    String Input::GetKeyName(KeyCode KeyCode)
    {
        switch (KeyCode) {
        case KeyCode::UNKNOWN: return "Unknown Key";
        case KeyCode::SPACE: return "Space";
        case KeyCode::APOSTROPHE: return "Apostrophe";
        case KeyCode::COMMA: return "Comma";
        case KeyCode::MINUS: return "Minus";
        case KeyCode::PERIOD: return "Period";
        case KeyCode::SLASH: return "Slash";
        case KeyCode::KEY_0: return "Key 0";
        case KeyCode::KEY_1: return "Key 1";
        case KeyCode::KEY_2: return "Key 2";
        case KeyCode::KEY_3: return "Key 3";
        case KeyCode::KEY_4: return "Key 4";
        case KeyCode::KEY_5: return "Key 5";
        case KeyCode::KEY_6: return "Key 6";
        case KeyCode::KEY_7: return "Key 7";
        case KeyCode::KEY_8: return "Key 8";
        case KeyCode::KEY_9: return "Key 9";
        case KeyCode::SEMICOLON: return "Semicolon";
        case KeyCode::EQUAL: return "Equal";
        case KeyCode::KEY_A: return "A Key";
        case KeyCode::KEY_B: return "B Key";
        case KeyCode::KEY_C: return "C Key";
        case KeyCode::KEY_D: return "D Key";
        case KeyCode::KEY_E: return "E Key";
        case KeyCode::KEY_F: return "F Key";
        case KeyCode::KEY_G: return "G Key";
        case KeyCode::KEY_H: return "H Key";
        case KeyCode::KEY_I: return "I Key";
        case KeyCode::KEY_J: return "J Key";
        case KeyCode::KEY_K: return "K Key";
        case KeyCode::KEY_L: return "L Key";
        case KeyCode::KEY_M: return "M Key";
        case KeyCode::KEY_N: return "N Key";
        case KeyCode::KEY_O: return "O Key";
        case KeyCode::KEY_P: return "P Key";
        case KeyCode::KEY_Q: return "Q Key";
        case KeyCode::KEY_R: return "R Key";
        case KeyCode::KEY_S: return "S Key";
        case KeyCode::KEY_T: return "T Key";
        case KeyCode::KEY_U: return "U Key";
        case KeyCode::KEY_V: return "V Key";
        case KeyCode::KEY_W: return "W Key";
        case KeyCode::KEY_X: return "X Key";
        case KeyCode::KEY_Y: return "Y Key";
        case KeyCode::KEY_Z: return "Z Key";
        case KeyCode::LEFT_BRACKET: return "Left Bracket";
        case KeyCode::BACKSLASH: return "Backslash";
        case KeyCode::RIGHT_BRACKET: return "Right Bracket";
        case KeyCode::GRAVE_ACCENT: return "Grave Accent";
        case KeyCode::WORLD_1: return "World 1";
        case KeyCode::WORLD_2: return "World 2";
        case KeyCode::ESCAPE: return "Escape";
        case KeyCode::ENTER: return "Enter";
        case KeyCode::TAB: return "Tab";
        case KeyCode::BACKSPACE: return "Backspace";
        case KeyCode::INSERT: return "Insert";
        case KeyCode::DELETE_KEY: return "Delete";
        case KeyCode::RIGHT: return "Right";
        case KeyCode::LEFT: return "Left";
        case KeyCode::DOWN: return "Down";
        case KeyCode::UP: return "Up";
        case KeyCode::PAGE_UP: return "Page Up";
        case KeyCode::PAGE_DOWN: return "Page Down";
        case KeyCode::HOME: return "Home";
        case KeyCode::END: return "End";
        case KeyCode::CAPS_LOCK: return "Caps Lock";
        case KeyCode::SCROLL_LOCK: return "Scroll Lock";
        case KeyCode::NUM_LOCK: return "Num Lock";
        case KeyCode::PRINT_SCREEN: return "Print Screen";
        case KeyCode::PAUSE: return "Pause";
        case KeyCode::F1:  return "F1";
        case KeyCode::F2:  return "F2";
        case KeyCode::F3:  return "F3";
        case KeyCode::F4:  return "F4";
        case KeyCode::F5:  return "F5";
        case KeyCode::F6:  return "F6";
        case KeyCode::F7:  return "F7";
        case KeyCode::F8:  return "F8";
        case KeyCode::F9:  return "F9";
        case KeyCode::F10: return "F10";
        case KeyCode::F11: return "F11";
        case KeyCode::F12: return "F12";
        case KeyCode::F13: return "F13";
        case KeyCode::F14: return "F14";
        case KeyCode::F15: return "F15";
        case KeyCode::F16: return "F16";
        case KeyCode::F17: return "F17";
        case KeyCode::F18: return "F18";
        case KeyCode::F19: return "F19";
        case KeyCode::F20: return "F20";
        case KeyCode::F21: return "F21";
        case KeyCode::F22: return "F22";
        case KeyCode::F23: return "F23";
        case KeyCode::F24: return "F24";
        case KeyCode::F25: return "F25";
        case KeyCode::NUMPAD_0: return "Numpad 0";
        case KeyCode::NUMPAD_1: return "Numpad 1";
        case KeyCode::NUMPAD_2: return "Numpad 2";
        case KeyCode::NUMPAD_3: return "Numpad 3";
        case KeyCode::NUMPAD_4: return "Numpad 4";
        case KeyCode::NUMPAD_5: return "Numpad 5";
        case KeyCode::NUMPAD_6: return "Numpad 6";
        case KeyCode::NUMPAD_7: return "Numpad 7";
        case KeyCode::NUMPAD_8: return "Numpad 8";
        case KeyCode::NUMPAD_9: return "Numpad 9";
        case KeyCode::NUMPAD_DECIMAL: return "Numpad Decimal";
        case KeyCode::NUMPAD_DIVIDE: return "Numpad Divide";
        case KeyCode::NUMPAD_MULTIPLY: return "Numpad Multiply";
        case KeyCode::NUMPAD_SUBTRACT: return "Numpad Subtract";
        case KeyCode::NUMPAD_ADD: return "Numpad Add";
        case KeyCode::NUMPAD_ENTER: return "Numpad Enter";
        case KeyCode::NUMPAD_EQUAL: return "Numpad Equal";
        case KeyCode::LEFT_SHIFT: return "Left Shift";
        case KeyCode::LEFT_CONTROL: return "Left Control";
        case KeyCode::LEFT_ALT: return "Left Alt";
        case KeyCode::LEFT_SUPER: return "Left Super";
        case KeyCode::RIGHT_SHIFT: return "Left Shift";
        case KeyCode::RIGHT_CONTROL: return "Right Control";
        case KeyCode::RIGHT_ALT: return "Right Alt";
        case KeyCode::RIGHT_SUPER: return "Right Super";
        case KeyCode::MENU: return "Menu";
        }
        return "Unknown";
    }

    bool Input::GetMouseButtonDown(MouseButton MouseButton)
    {
        return s_MouseButtonStates[MouseButton] == InputState::Pressed;
    }

    bool Input::GetMouseButton(MouseButton MouseButton)
    {
        const Ref<Window>& Window = g_Application->GetWindow();
        const int State = glfwGetMouseButton(Window->GetNativeWindow(), (int)MouseButton);
        return State == GLFW_PRESS;
    }

    bool Input::GetMouseButtonUp(MouseButton MouseButton)
    {
        return s_MouseButtonStates[MouseButton] == InputState::Released;
    }

    Vector2 Input::GetMousePosition()
    {
        GLFWwindow* NativeWindow = g_Application->GetWindow()->GetNativeWindow();
        f64 X, Y;
        glfwGetCursorPos(NativeWindow, &X, &Y);
        return {(f32)X, (f32)Y};
    }

    const Array<u8>& Input::GetGamepadButtons(size_t ID)
    {
        return s_GamepadButtons[ID];
    }


    void Input::UpdateGamepadButtons()
    {
        for(size_t i = 0; i < 16; ++i)
        {
            int ButtonCount;
            const u8* Buttons = glfwGetJoystickButtons((int)i, &ButtonCount);
            s_GamepadButtons[i] = Array(Buttons, ButtonCount);
            for(size_t j = 0 ; j < s_GamepadButtons.Count(); ++j)
            {
                if(s_GamepadButtons.Count() == s_LastGamepadButtons.Count() && !s_GamepadButtons[i].IsEmpty() && !s_LastGamepadButtons[i].IsEmpty())
                {
                    if(s_GamepadButtons[i][j] != s_LastGamepadButtons[i][j])
                    {
                        const InputState State = s_GamepadButtons[i][j] ? InputState::Pressed : InputState::Released;
                        ApplicationDelegates::OnGamepadButtonEvent.BroadcastChecked(j, State);
                    }
                }
                
            }
            s_LastGamepadButtons[i] = s_GamepadButtons[i];
        }
    }

    void Input::ResetInputStates()
    {
        for(auto& [Key, State] : s_KeyStates)
        {
            State = InputState::None;
        }

        for(auto& [MouseButton, State] : s_MouseButtonStates)
        {
            State = InputState::None;
        }

        s_LastGamepadButtons = s_GamepadButtons;
    }
    
}
