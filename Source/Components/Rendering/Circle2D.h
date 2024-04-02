#pragma once
#include "Renderer.h"

namespace Hydro
{
    class VertexBuffer;
    class VertexArray;
    class IndexBuffer;
    class Shader;
    
    class Circle2D : public Renderer
    {
    public:
        Circle2D();

        void OnInit() override;
        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnUpdate(float Delta) override;
    
    private:
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<VertexArray> m_VertexArray;
        Ref<IndexBuffer> m_IndexBuffer;
        Ref<Shader> m_Shader;
    };
}
