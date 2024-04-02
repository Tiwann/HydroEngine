#pragma once
#include "Renderer.h"

namespace Hydro
{
    class VertexBuffer;
    class VertexArray;
    class IndexBuffer;
    class Shader;
    class Texture2D;
    
    class Sprite2D : public Renderer
    {
    public:
        Sprite2D();
        void OnInit() override;
        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnUpdate(float Delta) override;

        void SetTexture(const Ref<Texture2D>& Texture);
    private:
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<VertexArray> m_VertexArray;
        Ref<IndexBuffer> m_IndexBuffer;
        Ref<Shader> m_Shader;
        Ref<Texture2D> m_Texture;
    };
}
