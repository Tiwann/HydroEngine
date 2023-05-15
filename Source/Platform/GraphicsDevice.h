#pragma once
#include "HydroPCH.h"
#include "Core/Color.h"

namespace Hydro
{
    class Application;
    class HYDRO_API GraphicsDevice
    {
    public:
        GraphicsDevice(Application& application);
        virtual ~GraphicsDevice() = default;
        static GraphicsDevice* Create(Application& Application);

        virtual void ClearDepthBuffer() = 0;
        virtual void ClearColor(Color color) = 0;
        virtual void SwapBuffers() = 0;

    protected:
        Handle m_Handle{0};
        Application& m_Application;
    };
}
