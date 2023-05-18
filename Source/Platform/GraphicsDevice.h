#pragma once
#include "HydroPCH.h"
#include "Core/Color.h"

namespace Hydro
{
    class Application;
    class HYDRO_API GraphicsDevice
    {
    public:
        GraphicsDevice() = default;
        virtual ~GraphicsDevice() = default;
        static GraphicsDevice* Create();

        virtual void ClearDepthBuffer() = 0;
        virtual void ClearColor(Color color) = 0;
        virtual void SwapBuffers() = 0;
        virtual void DrawIndexed() = 0;
        //virtual VertexBuffer* CreateVertexBuffer();

    protected:
        Handle m_Handle{0};
    };
}
