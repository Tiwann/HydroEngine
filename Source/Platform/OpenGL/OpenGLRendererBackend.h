#pragma once
#include "Core/CullMode.h"
#include "Core/RendererBackend.h"
#include "Core/LogCategory.h"
#include "Core/LogVerbosity.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(OpenGL, "OPENGL");

namespace Hydro
{
    class Shader;
    
    class OpenGLRendererBackend : public RendererBackend
    {
    public:
        

        OpenGLRendererBackend(Application* Owner) : RendererBackend(Owner) {}
        ~OpenGLRendererBackend() override = default;

        bool Initialize() override;
        void Destroy() override;
        void ClearDepthBuffer() override;
        void ClearColorBuffer(const Color& color) override;
        void SwapBuffers() override;
        void Draw(DrawMode Mode, const Vao& VAO, uint32_t NumVert, const Ref<Shader>& Shader) override;
        void DrawIndexed(DrawMode Mode, const Ref<VertexArray>& VAO, const Ref<VertexBuffer>& VBO, const Ref<IndexBuffer>& IBO, const Ref<Shader>& Shader) override;
        void DrawLine(const Vector3& PointA, const Vector3& PointB, float Thickness, const Color& Color) override;
        void DrawWireQuad(const Vector3& Position, const Vector2& HalfExtents, float Thickness, const Color& Color) override;
        void DrawCircle(const Vector3& Position, float Radius, const Color& Color) override;
        void SetCullMode(CullMode Mode) override;

        GLenum GetOpenGLDrawMode(DrawMode Mode);
    protected:
        static std::string GetDebugSourceName(uint32_t Source);
        static Verbosity GetDebugVerbosity(uint32_t Severity);
    };
}
