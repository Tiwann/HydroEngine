#include "SpriteRenderer.h"

#include "Core/Application.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"
#include "Core/Shader.h"
#include "Core/Color.h"
#include "Core/RendererBackend.h"
#include "ResourceManager/ShaderManager.h"

#include "Core/Texture2D.h"
#include "Core/VertexBufferLayout.h"
#include "Editor/EditorGUI.h"
#include "ResourceManager/TextureManager.h"


namespace Hydro
{
    SpriteRenderer::SpriteRenderer(GameObject* Owner)
    : Renderer(Owner, "Sprite Renderer"), m_Sprite(nullptr, Vector2::Zero, Vector2::Zero), m_Tiling(Vector2::One)
    {
    }

    void SpriteRenderer::OnInit()
    {
        Renderer::OnInit();
        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();
        
        m_VertexBuffer = VertexBuffer::Create();
        m_IndexBuffer = IndexBuffer::Create({ 0, 2, 1, 0, 3, 2 });
        
        ShaderManager& Manager = Application::GetCurrentApplication().GetShaderManager();
        m_Shader = Manager.Retrieve("Sprite");
    }

    void SpriteRenderer::OnDestroy()
    {
        Renderer::OnDestroy();
        m_IndexBuffer.reset();
        m_VertexBuffer.reset();
        m_VertexArray.reset();
    }

    void SpriteRenderer::OnRender(const Ref<RendererBackend>& Renderer)
    {
        Renderer::OnRender(Renderer);
        if(!m_Shader) return;
        if(!m_Sprite.GetTexture()) return;

        const Vector2 Position = m_Sprite.GetPosition();
        const Vector2 Size = m_Sprite.GetSize();
        const float Width = m_Sprite.GetTexture()->GetSize().x;
        const float Height = m_Sprite.GetTexture()->GetSize().y;
        
        const Vector2 Uv0 = {Position.x / Width, (Position.y + Size.y) / Height};
        const Vector2 Uv1 = {(Position.x + Size.x) / Width, (Position.y + Size.y) / Height};
        const Vector2 Uv2 = {(Position.x + Size.x) / Width, Position.y / Height};
        const Vector2 Uv3 = {Position.x / Width, Position.y / Height};

         
        StaticArray<Vertex, 4> SpriteVertices = {
            {{-0.5f, +0.5f, 0.0f}, Uv0, Vector3::Zero, Color::White},
            {{+0.5f, +0.5f, 0.0f}, Uv1, Vector3::Zero, Color::White},
            {{+0.5f, -0.5f, 0.0f}, Uv2, Vector3::Zero, Color::White},
            {{-0.5f, -0.5f, 0.0f}, Uv3, Vector3::Zero, Color::White},
        };
        
        m_VertexArray->Bind();
        m_VertexBuffer->SendData(SpriteVertices.Data(), SpriteVertices.Count());
        m_VertexArray->SetBufferLayout(VertexBufferLayout::Default);
        
        
        m_Shader->Bind();
        m_Shader->SetUniformMat4("uModel", GetTransform()->GetWorldSpaceMatrix());

        if(m_Sprite.GetTexture())
        {
            const Vector2 TextureSize = m_Sprite.GetTexture()->GetSize();
            const float AspectRatio = TextureSize.x / TextureSize.y;
            
            const Vector2 NewSize = TextureSize.x < TextureSize.y
                ? Vector2(1.0f, AspectRatio)
                : Vector2(AspectRatio, 1.0f);

            const Matrix3 SpriteScale = Flags.Contains(SpriteRendererFlagBit::NormalizeSize)
            ? Math::Scale(Matrix3::Identity, NewSize)
            : Math::Scale(Matrix3::Identity, m_Sprite.GetSize() / (float)m_PixelsPerUnit);
            
            m_Shader->SetUniformMat3("uSpriteScale", SpriteScale);
            m_Shader->SetUniformTexture("uTexture", m_Sprite.GetTexture());
        }
        
        
        const Vector2 Tiling = Flags.Contains(SpriteRendererFlagBit::TileWithScale) ? (Vector2)GetTransform()->GetScale() : m_Tiling;
        const Vector2 HorizontalTiling = Flags.Contains(SpriteRendererFlagBit::FlipHorizontal) ? Vector2(-1.0f, 1.0f) : Vector2(1.0f, 1.0f);
        const Vector2 VerticalTiling = Flags.Contains(SpriteRendererFlagBit::FlipVertical) ? Vector2(1.0f, -1.0f) : Vector2(1.0f, 1.0f);
        const Vector2 FinalTiling = Tiling * HorizontalTiling * VerticalTiling;
        m_Shader->SetUniformFloat2("uTiling", FinalTiling);
        m_Shader->SetUniformFloat4("uColorTint", m_ColorTint);
        
        Renderer->DrawIndexed(DrawMode::Triangles, m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_Shader);
    }

    void SpriteRenderer::OnInspectorGUI(const ImGuiIO& IO)
    {
        Renderer::OnInspectorGUI(IO);

        
        UI::Sprite(m_Sprite);

        UI::DragVector2<float>("Tiling", m_Tiling, 0.1f);
        UI::DragVector2<float>("Size", m_Size, 0.1f);
        
        const char* FlagNames[] = { "None",
                                    "Tile With Scale",
                                    "Flip Horizontal",
                                    "Flip Vertical",
                                    "Normalize Size" };

        
        if(ImGui::BeginCombo("Flags", nullptr, ImGuiComboFlags_NoPreview))
        {
            for(size_t i = 1; i < std::size(FlagNames); i++)
            {
                bool IsSelected = Flags.Contains(SpriteRendererFlags(1 << i));
                if(ImGui::Selectable(FlagNames[i], &IsSelected))
                {
                    Flags.Toggle(SpriteRendererFlags(1 << i));
                }
            }
            ImGui::EndCombo();
        }

        ImGui::ColorEdit4("Tint", (float*)&m_ColorTint, ImGuiColorEditFlags_DisplayHex);
        UI::DragValue<int>("Pixels Per Unit", m_PixelsPerUnit, 1);
    }

    void SpriteRenderer::SetTiling(const Vector2& Tiling)
    {
        m_Tiling = Tiling;
    }

    Vector2 SpriteRenderer::GetTiling() const
    {
        return m_Tiling;
    }

    
    void SpriteRenderer::SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    Vector2 SpriteRenderer::GetSize() const
    {
        return m_Size;
    }

    Color SpriteRenderer::GetColorTint() const
    {
        return m_ColorTint;
    }

    void SpriteRenderer::SetColorTint(const Color& Color)
    {
        m_ColorTint = Color;
    }

    int32_t SpriteRenderer::GetPixelsPerUnit() const
    {
        return m_PixelsPerUnit;
    }

    void SpriteRenderer::SetPixelsPerUnit(int32_t PixelsPerUnit)
    {
        m_PixelsPerUnit = PixelsPerUnit;
    }

    Sprite SpriteRenderer::GetSprite() const
    {
        return m_Sprite;
    }

    void SpriteRenderer::SetSprite(const Sprite& sprite)
    {
        m_Sprite = sprite;
    }
}
