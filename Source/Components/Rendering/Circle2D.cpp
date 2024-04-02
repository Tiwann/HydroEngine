#include "HydroPCH.h"
#include "Circle2D.h"

#include "Components/Transform.h"
#include "Core/Color.h"
#include "Core/GameObject.h"
#include "Core/IndexBuffer.h"
#include "Core/Shader.h"
#include "Core/VertexBuffer.h"
#include "Core/Vertex.h"
#include "Core/VertexArray.h"
#include "Platform/PlatformRenderer.h"

namespace Hydro
{
    Circle2D::Circle2D() : Renderer("Circle2D")
    {
        
    }

    void Circle2D::OnInit()
    {
        Renderer::OnInit();

        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();

        Vertex Vertices[4] = {
            {{-0.5f, +0.5f, 0.0f}, {1.0f, 0.0f}, Vector3::Zero, Color::White},
            {{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f}, Vector3::Zero, Color::White},
            {{+0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}, Vector3::Zero, Color::White},
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

        constexpr std::string_view ShaderPath("Shaders/Circle.glsl");
        m_Shader = Shader::Create("CircleShader", ShaderPath, GLSL);
        m_Shader->Compile();
        m_Shader->Link();
        m_Shader->Validate();
    }

    void Circle2D::OnDestroy()
    {
        Renderer::OnDestroy();
    }

    void Circle2D::OnEnable()
    {
        Renderer::OnEnable();
    }

    void Circle2D::OnDisable()
    {
        Renderer::OnDisable();
    }

    void Circle2D::OnUpdate(float Delta)
    {
        Renderer::OnUpdate(Delta);
        m_Shader->Bind();
        const Matrix4 ModelMatrix = GetTransform()->GetMatrix();
        m_Shader->SetUniformMat4("uModelMatrix", ModelMatrix);
        m_RendererBackend->DrawIndexed(m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_Shader);
    }
}
