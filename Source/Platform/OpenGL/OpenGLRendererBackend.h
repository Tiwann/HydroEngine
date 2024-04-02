#pragma once
#include "Macros.h"
#include "Core/RendererBackend.h"
#include "Core/LogCategory.h"
#include "Core/LogVerbosity.h"
#include "Core/ShaderSource.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(OpenGL, "OPENGL");

namespace Hydro
{
    class Shader;
    
    class OpenGLRendererBackend : public RendererBackend
    {
    public:
        OpenGLRendererBackend();
        ~OpenGLRendererBackend() override;

        
        void ClearDepthBuffer() override;
        void ClearColor(const Color& color) override;
        void SwapBuffers() override;
        void DrawRect(const Rectangle& Rect, const Color& Color) override;
        void DrawCircle(const Rectangle& Rect, float Radius, const Color& Color) override;
        void DrawIndexed(const Ref<VertexArray>& VAO, const Ref<VertexBuffer>& VBO, const Ref<IndexBuffer>& IBO,
            const Ref<Shader>& Shader) override;

    protected:
        static std::string GetDebugSourceName(uint32_t Source);
        static Verbosity GetDebugVerbosity(uint32_t Severity);
    };
}
