#pragma once
#include "HydroPCH.h"
#include "Core/Application.h"
#include "Platform/GraphicsDevice.h"

namespace Hydro
{
    class HYDRO_API OpenGLDevice : public GraphicsDevice
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
