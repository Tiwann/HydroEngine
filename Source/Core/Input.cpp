#include "HydroPCH.h"
#include "Input.h"

#include <GLFW/glfw3.h>

#include "Application.h"
#include "Memory.h"
#include "Window.h"

namespace Hydro
{
    KeyState Input::States[TOTAL] = {};
    
    bool Input::GetKeyDown(KeyCode KeyCode)
    {
        Window& Window = Application::GetCurrentApplication().GetWindow();
        const int State = glfwGetKey(Window.GetNativeWindow(), (int)KeyCode);
        return State == GLFW_PRESS;
    }

    bool Input::GetKey(KeyCode KeyCode)
    {
        Window& Window = Application::GetCurrentApplication().GetWindow();
        const int State = glfwGetKey(Window.GetNativeWindow(), (int)KeyCode);
        return State == GLFW_PRESS;
    }

    bool Input::GetKeyUp(KeyCode KeyCode)
    {
        Window& Window = Application::GetCurrentApplication().GetWindow();
        const int State = glfwGetKey(Window.GetNativeWindow(), (int)KeyCode);
        return State == GLFW_RELEASE;
    }

    std::string Input::GetKeyName(KeyCode KeyCode)
    {
        switch (KeyCode) {
        case UNKNOWN: return "Unknown Key";
        case SPACE: return "Space";
        case APOSTROPHE: return "Apostrophe";
        case COMMA: return "Comma";
        case MINUS: return "Minus";
        case PERIOD: return "Period";
        case SLASH: return "Slash";
        case KEY_0: return "Key 0";
        case KEY_1: return "Key 1";
        case KEY_2: return "Key 2";
        case KEY_3: return "Key 3";
        case KEY_4: return "Key 4";
        case KEY_5: return "Key 5";
        case KEY_6: return "Key 6";
        case KEY_7: return "Key 7";
        case KEY_8: return "Key 8";
        case KEY_9: return "Key 9";
        case SEMICOLON: return "Semicolon";
        case EQUAL: return "Equal";
        case KEY_A: return "A Key";
        case KEY_B: return "B Key";
        case KEY_C: return "C Key";
        case KEY_D: return "D Key";
        case KEY_E: return "E Key";
        case KEY_F: return "F Key";
        case KEY_G: return "G Key";
        case KEY_H: return "H Key";
        case KEY_I: return "I Key";
        case KEY_J: return "J Key";
        case KEY_K: return "K Key";
        case KEY_L: return "L Key";
        case KEY_M: return "M Key";
        case KEY_N: return "N Key";
        case KEY_O: return "O Key";
        case KEY_P: return "P Key";
        case KEY_Q: return "Q Key";
        case KEY_R: return "R Key";
        case KEY_S: return "S Key";
        case KEY_T: return "T Key";
        case KEY_U: return "U Key";
        case KEY_V: return "V Key";
        case KEY_W: return "W Key";
        case KEY_X: return "X Key";
        case KEY_Y: return "Y Key";
        case KEY_Z: return "Z Key";
        case LEFT_BRACKET: return "Left Bracket";
        case BACKSLASH: return "Backslash";
        case RIGHT_BRACKET: return "Right Bracket";
        case GRAVE_ACCENT: return "Grave Accent";
        case WORLD_1: return "World 1";
        case WORLD_2: return "World 2";
        case ESCAPE: return "Escape";
        case ENTER: return "Enter";
        case TAB: return "Tab";
        case BACKSPACE: return "Backspace";
        case INSERT: return "Insert";
        case DELETE_KEY: return "Delete";
        case RIGHT: return "Right";
        case LEFT: return "Left";
        case DOWN: return "Down";
        case UP: return "Up";
        case PAGE_UP: return "Page Up";
        case PAGE_DOWN: return "Page Down";
        case HOME: return "Home";
        case END: return "End";
        case CAPS_LOCK: return "Caps Lock";
        case SCROLL_LOCK: return "Scroll Lock";
        case NUM_LOCK: return "Num Lock";
        case PRINT_SCREEN: return "Print Screen";
        case PAUSE: return "Pause";
        case F1:  return "F1";
        case F2:  return "F2";
        case F3:  return "F3";
        case F4:  return "F4";
        case F5:  return "F5";
        case F6:  return "F6";
        case F7:  return "F7";
        case F8:  return "F8";
        case F9:  return "F9";
        case F10: return "F10";
        case F11: return "F11";
        case F12: return "F12";
        case F13: return "F13";
        case F14: return "F14";
        case F15: return "F15";
        case F16: return "F16";
        case F17: return "F17";
        case F18: return "F18";
        case F19: return "F19";
        case F20: return "F20";
        case F21: return "F21";
        case F22: return "F22";
        case F23: return "F23";
        case F24: return "F24";
        case F25: return "F25";
        case NUMPAD_0: return "Numpad 0";
        case NUMPAD_1: return "Numpad 1";
        case NUMPAD_2: return "Numpad 2";
        case NUMPAD_3: return "Numpad 3";
        case NUMPAD_4: return "Numpad 4";
        case NUMPAD_5: return "Numpad 5";
        case NUMPAD_6: return "Numpad 6";
        case NUMPAD_7: return "Numpad 7";
        case NUMPAD_8: return "Numpad 8";
        case NUMPAD_9: return "Numpad 9";
        case NUMPAD_DECIMAL: return "Numpad Decimal";
        case NUMPAD_DIVIDE: return "Numpad Divide";
        case NUMPAD_MULTIPLY: return "Numpad Multiply";
        case NUMPAD_SUBTRACT: return "Numpad Subtract";
        case NUMPAD_ADD: return "Numpad Add";
        case NUMPAD_ENTER: return "Numpad Enter";
        case NUMPAD_EQUAL: return "Numpad Equal";
        case LEFT_SHIFT: return "Left Shift";
        case LEFT_CONTROL: return "Left Control";
        case LEFT_ALT: return "Left Alt";
        case LEFT_SUPER: return "Left Super";
        case RIGHT_SHIFT: return "Left Shift";
        case RIGHT_CONTROL: return "Right Control";
        case RIGHT_ALT: return "Right Alt";
        case RIGHT_SUPER: return "Right Super";
        case MENU: return "Menu";
        }
        return "Unknown";
    }

    KeyState Input::GetState(KeyCode KeyCode)
    {
        return States[(int)KeyCode];
    }
}
