#pragma once
#include "HydroPCH.h"
#include "Platform/RendererDevice.h"

namespace Hydro
{
    class HYDRO_API OpenGLDevice : public RendererDevice
    {
    public:
        OpenGLDevice();

        // GraphicsDevice
        void ClearDepthBuffer() override;
        void ClearColor(Color color) override;
        void SwapBuffers() override;
        void DrawIndexed() override;
    };
}
