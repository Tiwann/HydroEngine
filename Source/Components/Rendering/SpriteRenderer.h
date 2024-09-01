#pragma once
#include "Renderer.h"
#include "Core/Color.h"
#include "Core/Flags.h"
#include "Math/Vector2.h"
#include "Core/Sprite.h"

#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(SpriteRenderer, "SPRITE RENDERER")

namespace Hydro
{
    class VertexBuffer;
    class VertexArray;
    class IndexBuffer;
    class Shader;
    class Texture2D;

    enum class SpriteRendererFlagBit
    {
        None,
        HYDRO_FLAG_BIT(TileWithScale, 1),
        HYDRO_FLAG_BIT(FlipHorizontal, 2),
        HYDRO_FLAG_BIT(FlipVertical, 3),
        HYDRO_FLAG_BIT(NormalizeSize, 4),
        All = TileWithScale | FlipHorizontal | FlipVertical | NormalizeSize
    };

    HYDRO_DECLARE_FLAGS(SpriteRendererFlagBit, SpriteRendererFlags);
    
    class SpriteRenderer : public Renderer
    {
    public:
        SpriteRenderer(Entity* Owner);
        
        SpriteRendererFlags Flags;
        
        void OnInit() override;
        void OnDestroy() override;
        void OnRender(const Ref<RendererBackend>& Renderer) override;
        void OnInspectorGUI(const ImGuiIO& IO) override;
        
        /* Sprite  */
        Sprite GetSprite() const;
        void SetSprite(const Sprite& sprite);

        /* Tiling */
        void SetTiling(const Vector2& Tiling);
        Vector2 GetTiling() const;

        /* Size */
        void SetSize(const Vector2& Size);
        Vector2 GetSize() const;

        /* Color Tint */
        Color GetColorTint() const;
        void SetColorTint(const Color& Color);

        /* Pixels per unit */
        int32_t GetPixelsPerUnit() const;
        void SetPixelsPerUnit(int32_t PixelsPerUnit);

    private:
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<VertexArray> m_VertexArray;
        Ref<IndexBuffer> m_IndexBuffer;
        Ref<Shader> m_Shader;
        Sprite m_Sprite;

        int32_t m_PixelsPerUnit = 100;
        Vector2 m_Tiling{Vector2::One};
        Vector2 m_Size;
        Color m_ColorTint{Color::White};
    };
}
