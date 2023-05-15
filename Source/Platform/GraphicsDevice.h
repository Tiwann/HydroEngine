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

        virtual void Clear() { }
        virtual void Clear(Color color) { }
        virtual void SwapBuffers() {}

    protected:
        Handle m_Handle{0};
        Application& m_Application;
    };
}
