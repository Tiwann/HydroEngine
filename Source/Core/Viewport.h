#pragma once
#include "SharedPointer.h"
#include "Math/Vector2.h"


namespace Hydro
{
    class FrameBuffer;
    
    class Viewport
    {
    public:
        
    private:
        Ref<FrameBuffer> m_FrameBuffer;
        Vector2 m_Size;
    };
}
