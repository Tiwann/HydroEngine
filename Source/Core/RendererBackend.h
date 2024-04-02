#pragma once
#include "Core/SharedPointer.h"

namespace Hydro
{
    class Color;
    struct Rectangle;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Shader;
    
    class RendererBackend
    {
    public:
        RendererBackend() = default;
        static Ref<RendererBackend> Create();

        virtual ~RendererBackend() = default;
        virtual void ClearDepthBuffer() = 0;
        virtual void ClearColor(const Color& color) = 0;
        virtual void SwapBuffers() = 0;
        virtual void DrawRect(const Rectangle& Rect, const Color& Color) = 0;
        virtual void DrawCircle(const Rectangle& Rect, float Radius, const Color& Color) = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& VAO,
            const Ref<VertexBuffer>& VBO,
            const Ref<IndexBuffer>& IBO,
            const Ref<Shader>& Shader) = 0;


        bool IsReady() const;

    protected:
        bool m_IsReady = false;
    };
}
