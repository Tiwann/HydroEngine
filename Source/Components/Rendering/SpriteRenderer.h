#pragma once
#include "Renderer.h"
#include "Core/Color.h"
#include "Math/Vector2.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(SpriteRenderer, "SPRITE RENDERER")

namespace Hydro
{
    class VertexBuffer;
    class VertexArray;
    class IndexBuffer;
    class Shader;
    class Texture2D;
    
    class SpriteRenderer : public Renderer
    {
    public:
        SpriteRenderer(GameObject* Owner);
        
        void OnInit() override;
        void OnDestroy() override;
        void OnRender(const Ref<RendererBackend>& Renderer) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        
        void SetTexture(const Ref<Texture2D>& Texture);
        Ref<Texture2D> GetTexture() const;
        
        void SetTiling(const Vector2& Tiling);
        Vector2 GetTiling() const;
        
        void SetTileWithScale(bool Enable);
        bool IsTilingWithScale() const;
        
        void SetSize(const Vector2& Size);
        Vector2 GetSize() const;
        void SetFlipped(bool Flipped);

        Color GetColorTint() const;
        void SetColorTint(const Color& Color);

    private:
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<VertexArray> m_VertexArray;
        Ref<IndexBuffer> m_IndexBuffer;
        Ref<Shader> m_Shader;
        Ref<Texture2D> m_Texture;
        Vector2 m_Tiling{Vector2::One};
        Vector2 m_Size;
        Color m_ColorTint{Color::White};
        bool m_TileWithScale{false};
        bool m_Flipped{false};
    };
}
