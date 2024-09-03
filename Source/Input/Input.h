#pragma once
#include "GamepadButton.h"
#include "GamepadThumbstick.h"
#include "KeyCode.h"
#include "InputState.h"
#include "MouseButton.h"
#include "Core/Buffer.h"
#include "Core/Containers/String.h"
#include "Core/Containers/Map.h"
#include "Core/Buffer.h"
#include "Core/LogCategory.h"
#include <GLFW/glfw3.h>


constexpr int HYDRO_MAX_GAMEPADS = 16;

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Input, "INPUT")


namespace Hydro
{
    class Vector2;
    
    class Input
    {
    public:
        friend class Application;
        static bool GetKeyDown(KeyCode KeyCode);
        static bool GetKey(KeyCode KeyCode);
        static bool GetKeyUp(KeyCode KeyCode);
        static String GetKeyName(KeyCode KeyCode);

        static bool GetMouseButtonDown(MouseButton MouseButton);
        static bool GetMouseButton(MouseButton MouseButton);
        static bool GetMouseButtonUp(MouseButton MouseButton);
        
        static Vector2 GetMousePosition();

        static bool IsGamepadConnected(size_t ID);
        static BufferView<bool> GetGamepadButtons(size_t ID);
        static bool GetGamepadButtonDown(size_t ID, GamepadButton Button);
        static bool GetGamepadButtonUp(size_t ID, GamepadButton Button);
        static bool GetGamepadButton(size_t ID, GamepadButton Button);
        static Vector2 GetGamepadStick(size_t ID, GamepadThumbstick Thumbstick);
        static float GetGamepadLeftShoulder(size_t ID);
        static float GetGamepadRightShoulder(size_t ID);        
    private:
        inline static Map<KeyCode, InputState> s_KeyStates;
        inline static Map<MouseButton, InputState> s_MouseButtonStates;

        inline static StaticArray<GLFWgamepadstate, HYDRO_MAX_GAMEPADS> s_GamepadStates;
        inline static StaticArray<GLFWgamepadstate, HYDRO_MAX_GAMEPADS> s_LastGamepadStates;
        inline static StaticArray<StaticArray<InputState, 15>, HYDRO_MAX_GAMEPADS> s_GamepadButtons;
        inline static StaticArray<StaticArray<float, 6>, HYDRO_MAX_GAMEPADS> s_GamepadAxes;
        
        static void UpdateGamepads();
        static void ResetInputStates();
    };
}
