#pragma once
#include "KeyCode.h"
#include "InputState.h"
#include "MouseButton.h"
#include "GamepadButton.h"
#include "Core/Containers/String.h"
#include "Core/Containers/Map.h"
#include "Core/Containers/ArrayView.h"


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

        static const Array<u8>& GetGamepadButtons(size_t ID);
    private:
        inline static Map<KeyCode, InputState> s_KeyStates;
        inline static Map<MouseButton, InputState> s_MouseButtonStates;
        
        inline static StaticArray<Array<u8>, 16> s_GamepadButtons;
        inline static StaticArray<Array<u8>, 16> s_LastGamepadButtons;
        

        static void UpdateGamepadButtons();
        static void ResetInputStates();
    };
}
