#pragma once
#include "Macros.h"
#include "Platform/RendererDevice.h"
#include "Core/LogCategory.h"
#include "Core/LogVerbosity.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(OpenGL, "OPENGL");

namespace Hydro
{
    class HYDRO_API OpenGLDevice : public RendererDevice
    {
    public:
        OpenGLDevice();

        // GraphicsDevice
        void ClearDepthBuffer() override;
        void ClearColor(const Color& color) override;
        void SwapBuffers() override;
        void DrawIndexed() override;

        static std::string GetDebugSourceName(uint32_t Source);
        static Verbosity GetDebugVerbosity(uint32_t Severity);
    };
}
