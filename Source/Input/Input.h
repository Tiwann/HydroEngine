#pragma once
#include "KeyCode.h"
#include "InputState.h"
#include "MouseButton.h"
#include "Core/Containers/String.h"
#include "Core/Containers/Map.h"


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
    private:
        inline static Map<KeyCode, InputState> s_KeyStates;
        inline static Map<MouseButton, InputState> s_MouseButtonStates;
        
        static void ResetInputStates();
    };
}
