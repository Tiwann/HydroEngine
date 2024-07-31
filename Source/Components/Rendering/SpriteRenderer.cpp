#include "HydroPCH.h"
#include "SpriteRenderer.h"

#include "Core/Application.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"
#include "Core/Shader.h"
#include "Core/Color.h"
#include "Core/PopupMessage.h"
#include "Core/RendererBackend.h"
#include "Core/ShaderManager.h"

#include "Core/Texture2D.h"
#include "Core/VertexBufferLayout.h"
#include "Platform/OpenGL/OpenGLRendererBackend.h"

namespace Hydro
{
    SpriteRenderer::SpriteRenderer(GameObject* Owner) : Renderer(Owner, "Sprite"), m_Tiling(Vector2::One)
    {
    }

    void SpriteRenderer::OnInit()
    {
        Renderer::OnInit();
        
        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();
        
        Vertex Vertices[4] = {
            {{-0.5f, +0.5f, 0.0f}, {0.0f, 1.0f}, Vector3::Zero, Color::White},
            {{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f}, Vector3::Zero, Color::White},
            {{+0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, Vector3::Zero, Color::White},
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, Vector3::Zero, Color::White},
        };
        
        m_VertexBuffer = VertexBuffer::Create(Vertices, std::size(Vertices));
        
        m_IndexBuffer = IndexBuffer::Create({ 0, 2, 1, 0, 3, 2 });
        
        m_VertexArray->SetBufferLayout(VertexBufferLayout::Default);

        ShaderManager& Manager = Application::GetCurrentApplication().GetShaderManager();
        m_Shader = Manager.Retrieve("Sprite2D");
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
        m_Shader->Bind();
        m_Shader->SetUniformMat4("uModel", GetTransform()->GetWorldSpaceMatrix());

        if(m_Texture)
        {
            // Calculate aspect ratio
            const Vector2 Size = m_Texture->GetSize();
            const float AspectRatio = Size.x / Size.y;
            
            const Vector2 NewSize = Size.x < Size.y
                ? Vector2(1.0f, AspectRatio)
                : Vector2(AspectRatio, 1.0f);

            Matrix3 TextureScale = Matrix3::Identity;
            TextureScale.Scale(NewSize);
            m_Shader->SetUniformMat3("uTextureScale", TextureScale);
            m_Shader->SetUniformTexture("uTexture", m_Texture);
        }
        
        
        const Vector2 Tiling = m_TileWithScale ? (Vector2)GetTransform()->GetScale() : m_Tiling;
        const Vector2 FinalTiling = m_Flipped ? Tiling * Vector2(-1.0f, 1.0f) : Tiling;
        m_Shader->SetUniformFloat2("uTiling", FinalTiling);
        m_Shader->SetUniformFloat4("uColorTint", m_ColorTint);

        auto Rend = Cast<OpenGLRendererBackend>(Renderer);
        Rend->DrawIndexed(DrawMode::Triangles, m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_Shader);
    }

    void SpriteRenderer::OnInspectorGUI(const ImGuiIO& IO)
    {
        Renderer::OnInspectorGUI(IO);
        ImGui::PushID((const void*)m_Guid);
        if(ImGui::TreeNode(m_Name.c_str()))
        {
            ImGui::Image((ImTextureID)m_Texture->GetHandle(), ImVec2(m_Texture->GetSize().x, m_Texture->GetSize().y),
                ImVec2(1, 1), ImVec2(0, 0));
            
            ImGui::DragFloat2("Tiling", m_Tiling.ValuePtr());
            ImGui::DragFloat2("Size", m_Size.ValuePtr());
            ImGui::Checkbox("Tile With Scale", &m_TileWithScale);
            ImGui::Checkbox("Flipped", &m_Flipped);
            ImGui::ColorEdit4("Tint", (float*)&m_ColorTint, ImGuiColorEditFlags_DisplayHex);
            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    void SpriteRenderer::SetTexture(const Ref<Texture2D>& Texture)
    {
        m_Texture = Texture;
    }

    Ref<Texture2D> SpriteRenderer::GetTexture() const
    {
        return m_Texture;
    }

    void SpriteRenderer::SetTiling(const Vector2& Tiling)
    {
        m_Tiling = Tiling;
    }

    Vector2 SpriteRenderer::GetTiling() const
    {
        return m_Tiling;
    }

    void SpriteRenderer::SetTileWithScale(bool Enable)
    {
        m_TileWithScale = Enable;
    }

    bool SpriteRenderer::IsTilingWithScale() const
    {
        return m_TileWithScale;
    }

    void SpriteRenderer::SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    Vector2 SpriteRenderer::GetSize() const
    {
        return m_Size;
    }

    void SpriteRenderer::SetFlipped(bool Flipped)
    {
        m_Flipped = Flipped;
    }

    Color SpriteRenderer::GetColorTint() const
    {
        return m_ColorTint;
    }

    void SpriteRenderer::SetColorTint(const Color& Color)
    {
        m_ColorTint = Color;
    }
}
