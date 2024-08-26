#pragma once
#include "CullMode.h"
#include "Core/SharedPointer.h"
#include "Math/Matrix4.h"


namespace Hydro
{
    class Color;
    struct Rectangle;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Shader;
    class Camera;
    class Application;
    class Vector3;
    class Vector2;
    class Sprite;
    
    enum class DrawMode
    {
        Points,
        Lines,
        LineStrip,
        LineLoop,
        Triangles,
    };
    
    class RendererBackend
    {
    protected:
        using Vao = Ref<VertexArray>;
        using Vbo = Ref<VertexBuffer>;
        using Ibo = Ref<IndexBuffer>;
    public:
        RendererBackend(Application* Owner) : m_Application(*Owner) {}
        static Ref<RendererBackend> Create(Application* Owner);

        virtual ~RendererBackend() = default;
        virtual bool Initialize() = 0;
        virtual void Destroy() = 0;
        virtual void ClearDepthBuffer() = 0;
        virtual void ClearColorBuffer(const Color& color) = 0;
        virtual void SwapBuffers() = 0;
        virtual void SetViewportRect(Vector2 Position, Vector2 Size) = 0;
        virtual void Draw(DrawMode Mode, const Vao& VAO, uint32_t NumVert, const Ref<Shader>& Shader) = 0;
        virtual void DrawIndexed(DrawMode Mode, const Vao& VAO, const Vbo& VBO, const Ibo& IBO, const Ref<Shader>& Shader) = 0;
        virtual void DrawLine(const Vector3& PosA, const Vector3& PosB, float Thickness, const Color& Color) = 0;
        virtual void DrawWireQuad(const Matrix4& Transform, const Vector3& Position, const Vector2& HalfExtents, float Thickness, const Color& Color) = 0;
        virtual void DrawCircle(const Matrix4& Transform, const Vector3& Position, float Radius, const Color& Color) = 0;
        virtual void SetCullMode(CullMode Mode);

        bool IsReady() const;
        void SetCurrentCamera(const Ref<Camera>& Camera);
        Ref<Camera> GetCurrentCamera();

    protected:
        bool m_IsReady = false;
        Ref<Camera> m_CurrentCamera;
        Application& m_Application;
        CullMode m_CullMode{CullMode::BackFace};
    };
}
