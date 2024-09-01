#include "OpenGLRendererBackend.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include "Core/Color.h"
#include "Core/LogVerbosity.h"
#include "Core/Vertex.h"

#include "Components/Camera.h"
#include "Core/Shader.h"
#include "Core/IndexBuffer.h"
#include "ResourceManager/ShaderManager.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"
#include "Core/VertexBufferLayout.h"
#include "Math/LinearAlgebra.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Hydro
{
    bool OpenGLRendererBackend::Initialize()
    {
        Application& application = *g_Application;
        HYDRO_LOG(OpenGL, Verbosity::Trace, "Creating OpenGL context");
        glfwMakeContextCurrent(application.GetWindow()->GetNativeWindow());
        glfwSwapInterval(1);
        
        if(!gladLoadGL(glfwGetProcAddress))
        {
            HYDRO_LOG(OpenGL, Verbosity::Error, "Failed to retrieve OpenGL function pointers!");
            application.RequireExit();
            return false;
        }
        
        const auto Callback = [](GLenum Source, GLenum, GLuint, GLenum Severity, GLsizei, const GLchar *Message, const void *) -> void
        {
            const Verbosity Verbo = GetDebugVerbosity(Severity);
            const std::string SourceName = GetDebugSourceName(Source);
            if(Verbo < Verbosity::Warning)
                return;
            HYDRO_LOG(OpenGL, Verbo, "Debug ({}): {}", SourceName, Message);
        };

#if defined(HYDRO_DEBUG)
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(Callback, nullptr);
#endif
        
        glEnable(GL_MULTISAMPLE);

        const std::string Renderer = (const char*)glGetString(GL_RENDERER);
        HYDRO_LOG(OpenGL, Verbosity::Info, "Using OpenGL 4.6");
        HYDRO_LOG(OpenGL, Verbosity::Info, "Using GPU: {}", Renderer);

        return true;
    }

    void OpenGLRendererBackend::Destroy()
    {
    }

    void OpenGLRendererBackend::ClearDepthBuffer()
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererBackend::ClearColorBuffer(const Color& color)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererBackend::SwapBuffers()
    {
        glfwSwapBuffers(g_Application->GetWindow()->GetNativeWindow());
    }

    void OpenGLRendererBackend::SetViewportRect(Vector2 Position, Vector2 Size)
    {
        glViewport((GLint)Position.x, (GLint)Position.y, (GLint)Size.x, (GLint)Size.y);
    }

    void OpenGLRendererBackend::Draw(DrawMode Mode, const Vao& VAO, uint32 NumVert, const Ref<Shader>& Shader)
    {
        VAO->Bind();
        Shader->Bind();
        if(m_CurrentCamera)
        {
            Shader->SetUniformMat4("uView", m_CurrentCamera->GetViewMatrix());
            Shader->SetUniformMat4("uProjection", m_CurrentCamera->GetProjectionMatrix());
        } else
        {
            HYDRO_LOG(OpenGL, Verbosity::Warning, "No camera component found! No view-projection matrix sent.");
        }

        glDrawArrays(GetOpenGLDrawMode(Mode), 0, NumVert);
    }

    void OpenGLRendererBackend::DrawIndexed(DrawMode Mode, const Ref<VertexArray>& VAO, const Ref<VertexBuffer>& VBO, const Ref<IndexBuffer>& IBO, const Ref<Shader>& Shader)
    {
        VAO->Bind();
        VBO->Bind();
        IBO->Bind();
        Shader->Bind();
        if(m_CurrentCamera)
        {
            Shader->SetUniformMat4("uView", m_CurrentCamera->GetViewMatrix());
            Shader->SetUniformMat4("uProjection", m_CurrentCamera->GetProjectionMatrix());
        } else
        {
            HYDRO_LOG(OpenGL, Verbosity::Warning, "No camera component found! No view-projection matrix sent.");
        }
        glDrawElements(GetOpenGLDrawMode(Mode), (GLsizei)IBO->Count(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererBackend::DrawLine(const Vector3& PointA, const Vector3& PointB, float Thickness, const Color& Color)
    {
        auto vao = VertexArray::Create();
        vao->Bind();
        Vertex Points[] ={
            { PointA, Vector2::Zero, Vector3::Zero, Color },    
            { PointB, Vector2::Zero, Vector3::Zero, Color },    
        };
        auto vbo = VertexBuffer::Create(Points, std::size(Points));
        auto ibo = IndexBuffer::Create({0, 1});

        vao->SetBufferLayout(VertexBufferLayout::Default);
        
        auto shader = m_Application.GetShaderManager().Retrieve("UniformColor");
        shader->Bind();
        

        Matrix4 Model = Matrix4::Identity;
        Model.Scale({1.0f, 1.0f, 1.0f});
        shader->SetUniformMat4("uModel", Model);
        
        glLineWidth(Thickness);
    
        DrawIndexed(DrawMode::Lines, vao, vbo, ibo, shader);
        ibo.reset();
        vbo.reset();
        vao.reset();
    }

    void OpenGLRendererBackend::DrawWireQuad(const Matrix4& Transform, const Vector3& Position, const Vector2& HalfExtents, float Thickness, const Color& Color)
    {
        auto vao = VertexArray::Create();
        vao->Bind();
        StaticArray<Vertex, 4> Points
        {
            { Position + Vector3(-HalfExtents.x, HalfExtents.y, 0.0f) , Vector2::Zero, Vector3::Zero, Color },    
            { Position + Vector3(+HalfExtents.x, HalfExtents.y, 0.0f) , Vector2::Zero, Vector3::Zero, Color },
            { Position + Vector3(+HalfExtents.x, -HalfExtents.y, 0.0f) , Vector2::Zero, Vector3::Zero, Color },
            { Position + Vector3(-HalfExtents.x, -HalfExtents.y, 0.0f) , Vector2::Zero, Vector3::Zero, Color },
        };
        auto vbo = VertexBuffer::Create(Points, Points.Count());
        auto ibo = IndexBuffer::Create({0, 1, 2, 3});

        vao->SetBufferLayout(VertexBufferLayout::Default);
        
        auto shader = m_Application.GetShaderManager().Retrieve("UniformColor");
        shader->Bind();
        shader->SetUniformMat4("uModel", Transform);
        
        glLineWidth(Thickness);
    
        DrawIndexed(DrawMode::LineLoop, vao, vbo, ibo, shader);
        ibo.reset();
        vbo.reset();
        vao.reset();
    }

    void OpenGLRendererBackend::DrawCircle(const Matrix4& Transform, const Vector3& Position, float Radius, const Color& Color)
    {
        auto vao = VertexArray::Create();
        vao->Bind();
        Vertex Points[] ={
            { Position + Vector3(-Radius, +Radius, 0.0f) , {0.0f, 1.0f}, Vector3::Zero, Color },    
            { Position + Vector3(+Radius, +Radius, 0.0f) , {1.0f, 1.0f}, Vector3::Zero, Color },
            { Position + Vector3(+Radius, -Radius, 0.0f) , {1.0f, 0.0f}, Vector3::Zero, Color },
            { Position + Vector3(-Radius, -Radius, 0.0f) , {0.0f, 0.0f}, Vector3::Zero, Color },
        };
        auto vbo = VertexBuffer::Create(Points, std::size(Points));
        auto ibo = IndexBuffer::Create({0, 1, 2, 3});

        vao->SetBufferLayout(VertexBufferLayout::Default);
        
        auto shader = m_Application.GetShaderManager().Retrieve("Circle");
        shader->Bind();
        
        shader->SetUniformMat4("uModel", Transform);
        shader->SetUniformFloat("uThickness", 0.2f);
        shader->SetUniformFloat("uSmoothness", 0.05f);

        DrawIndexed(DrawMode::Triangles, vao, vbo, ibo, shader);
        ibo.reset();
        vbo.reset();
        vao.reset();
    }

    void OpenGLRendererBackend::SetCullMode(CullMode Mode)
    {
        switch(Mode)
        {
        case CullMode::FrontFace:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            break;
        case CullMode::BackFace:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            break;
        case CullMode::FrontAndBackFaces:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT_AND_BACK);
            break;
        case CullMode::None:
            glDisable(GL_CULL_FACE);
            break;
        }
    }

    GLenum OpenGLRendererBackend::GetOpenGLDrawMode(DrawMode Mode)
    {
        switch (Mode)
        {
        case DrawMode::Points: return GL_POINTS;
        case DrawMode::Lines: return GL_LINES;
        case DrawMode::LineStrip: return GL_LINE_STRIP;
        case DrawMode::Triangles: return GL_TRIANGLES;
        case DrawMode::LineLoop: return GL_LINE_LOOP;
        }
        return 0;
    }


    std::string OpenGLRendererBackend::GetDebugSourceName(uint32 Source)
    {
        switch (Source)
        {
        case GL_DEBUG_SOURCE_API : return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:	return "WINDOW SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
        case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER: return "OTHER";
        default: return "UNKNOWN";
        }
    }

    Verbosity OpenGLRendererBackend::GetDebugVerbosity(uint32 Severity)
    {
        switch (Severity)
        {
        case GL_DEBUG_SEVERITY_HIGH: return Verbosity::Error;
        case GL_DEBUG_SEVERITY_MEDIUM:
        case GL_DEBUG_SEVERITY_LOW: return Verbosity::Warning;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
        default: return Verbosity::Trace;
        }
    }
}

