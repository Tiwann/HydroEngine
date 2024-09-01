﻿#include "Core/Cursors.h"

#include "Window.h"
#include <GLFW/glfw3.h>


namespace Hydro
{
    void Cursor::SetCursorStandard(const Ref<Window>& Window, StandardCursors Cursors)
    {
        GLFWcursor* Cursor = glfwCreateStandardCursor(StandardCursorConvert(Cursors));
        glfwSetCursor(Window->GetNativeWindow(), Cursor);
    }

    void Cursor::SetCursorVisible(const Ref<Window>& Window, bool Visible)
    {
        const int32 Value = Visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN;
        glfwSetInputMode(Window->GetNativeWindow(), GLFW_CURSOR, Value);
    }

    void Cursor::SetCursorLocked(const Ref<Window>& Window, bool Locked)
    {
        const int32 Value = Locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
        glfwSetInputMode(Window->GetNativeWindow(), GLFW_CURSOR, Value);
    }

    int Cursor::StandardCursorConvert(StandardCursors Cursors)
    {
        switch (Cursors) {
        case StandardCursors::Arrow: return GLFW_ARROW_CURSOR;
        case StandardCursors::IBeam: return GLFW_IBEAM_CURSOR;
        case StandardCursors::Crosshair: return GLFW_CROSSHAIR_CURSOR;
        case StandardCursors::Hand: return GLFW_HAND_CURSOR;
        case StandardCursors::HorizontalResize: return GLFW_HRESIZE_CURSOR;
        case StandardCursors::VerticalResize: return GLFW_VRESIZE_CURSOR;
        }
        return 0;
    }
}
