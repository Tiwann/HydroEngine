#pragma once
#include "HydroPCH.h"
#include "Core/Color.h"

namespace Hydro
{
    class Application;
    class HYDRO_API RendererDevice
    {
    public:
        RendererDevice() = default;
        static RendererDevice* Create();

        virtual ~RendererDevice() = default;
        virtual void ClearDepthBuffer() = 0;
        virtual void ClearColor(Color color) = 0;
        virtual void SwapBuffers() = 0;
        virtual void DrawIndexed() = 0;

        bool IsReady() const;

    protected:
        bool m_IsReady = false;
    };
}
