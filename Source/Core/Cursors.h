#pragma once
#include "SharedPointer.h"

namespace Hydro
{
    class Window;
    
    using StandardCursors = enum
    {
        Arrow,
        IBeam,
        Crosshair,
        Hand,
        HorizontalResize,
        VerticalResize,
    };
    
    class Cursor
    {
    public:
        static void SetCursorStandard(const Ref<Window>& Window, StandardCursors Cursors);
        static void SetCursorVisible(const Ref<Window>& Window, bool Visible);
        static void SetCursorLocked(const Ref<Window>& Window, bool Locked);
    private:
        static int StandardCursorConvert(StandardCursors Cursors);
    };

    
}
