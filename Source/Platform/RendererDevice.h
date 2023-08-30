#pragma once
#include "Macros.h"

namespace Hydro
{
    class Application;
    class Color;
    
    class HYDRO_API RendererDevice
    {
    public:
        RendererDevice() = default;
        static RendererDevice* Create();

        virtual ~RendererDevice() = default;
        virtual void ClearDepthBuffer() = 0;
        virtual void ClearColor(const Color& color) = 0;
        virtual void SwapBuffers() = 0;
        virtual void DrawIndexed() = 0;

        bool IsReady() const;

    protected:
        bool m_IsReady = false;
    };
}
