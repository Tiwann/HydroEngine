#include "HydroPCH.h"
#include "Sprite2D.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"
#include "Core/IndexBuffer.h"
#include "Core/Shader.h"
#include "Core/Color.h"
#include "Core/RendererBackend.h"

namespace Hydro
{
    Sprite2D::Sprite2D() : Renderer("Sprite2D")
    {
    }

    void Sprite2D::OnInit()
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
        m_VertexBuffer->Bind();
        m_VertexBuffer->SendData();

        uint32_t Indices[6] = { 0, 1, 2, 0, 2, 3 };

        m_IndexBuffer = IndexBuffer::Create(Indices, std::size(Indices));
        m_IndexBuffer->Bind();
        m_IndexBuffer->SendData();

        m_VertexArray->SetBufferLayout();

        constexpr std::string_view ShaderPath("Shaders/Sprite2D.glsl");
        m_Shader = Shader::Create(m_Name, ShaderPath, GLSL);
        m_Shader->Compile();
        m_Shader->Link();
        m_Shader->Validate();
    }

    void Sprite2D::OnDestroy()
    {
        Renderer::OnDestroy();
        m_IndexBuffer.reset();
        m_VertexBuffer.reset();
        m_VertexArray.reset();
        m_Shader.reset();
    }

    void Sprite2D::OnEnable()
    {
        Renderer::OnEnable();
    }

    void Sprite2D::OnDisable()
    {
        Renderer::OnDisable();
    }

    void Sprite2D::OnUpdate(float Delta)
    {
        Renderer::OnUpdate(Delta);
        m_VertexArray->Bind();
        m_VertexBuffer->Bind();
        m_IndexBuffer->Bind();
        
        m_Shader->Bind();
        m_Shader->SetUniformMat4("uModelMatrix", GetTransform()->GetMatrix());
        m_Shader->SetUniformTexture("uTexture", m_Texture);
        m_RendererBackend->DrawIndexed(m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_Shader);
    }

    void Sprite2D::SetTexture(const Ref<Texture2D>& Texture)
    {
        m_Texture = Texture;
    }
}
