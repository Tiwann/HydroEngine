#include "HydroPCH.h"
#include "OpenGLRendererBackend.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include "Core/Color.h"
#include "Core/LogVerbosity.h"
#include "Core/Vertex.h"
#include <GLFW/glfw3.h>

#include "Core/Rectangle.h"
#include "Core/Shader.h"
#include "Components/Transform.h"
#include "Core/IndexBuffer.h"
#include "Core/VertexArray.h"
#include "Core/VertexBuffer.h"

#include "Math/Functions.h"
#include "Math/LinearAlgebra.h"

#define HYDRO_NO_UV_NO_NRM Vector2::Zero, Vector3::Zero
#define HYDRO_NO_UV Vector2::Zero
#define HYDRO_NO_NRM Vector3::Zero

#define HYDRO_COMPILE_SHADER(Shader) \
    if(!(Shader)->Compile()) \
    {\
        m_IsReady = false; \
        return; \
    } \
    if(!(Shader)->Link()) \
    {\
        m_IsReady = false; \
        return; \
    } \
    if(!(Shader)->Validate()) \
    {\
        m_IsReady = false; \
        return; \
    }((void)0)


namespace Hydro
{
    OpenGLRendererBackend::OpenGLRendererBackend() : RendererBackend()
    {
        Application& application = Application::GetCurrentApplication();
        HYDRO_LOG(OpenGL, Verbosity::Trace, "Creating OpenGL context");
        glfwMakeContextCurrent(application.GetWindow().GetNativeWindow());
        glfwSwapInterval(true);
        
        if(!gladLoadGL(glfwGetProcAddress))
        {
            HYDRO_LOG(OpenGL, Verbosity::Error, "Failed to retrieve OpenGL function pointers!");
            application.RequireExit();
            return;
        }
        
        const auto Callback = [](GLenum Source, GLenum, GLuint, GLenum Severity, GLsizei, const GLchar *Message, const void *) -> void
        {
            const Verbosity Verbo = GetDebugVerbosity(Severity);
            const std::string SourceName = GetDebugSourceName(Source);
            HYDRO_LOG(OpenGL, Verbo, "Debug ({}): {}", SourceName, Message);
        };

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_MULTISAMPLE); 
        glDebugMessageCallback(Callback, nullptr);
        
        std::string Renderer = (const char*)glGetString(GL_RENDERER);
        HYDRO_LOG(OpenGL, Info, "Using OpenGL 4.6");
        HYDRO_LOG(OpenGL, Info, "Using GPU: {}", Renderer);
        
        m_IsReady = true;
    }

    OpenGLRendererBackend::~OpenGLRendererBackend() = default;

    void OpenGLRendererBackend::ClearDepthBuffer()
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererBackend::ClearColor(const Color& color)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererBackend::SwapBuffers()
    {
        glfwSwapBuffers(Application::GetCurrentApplication().GetWindow().GetNativeWindow());
    }
    
    void OpenGLRendererBackend::DrawRect(const Rectangle& Rect, const Color& Color)
    {
        uint32_t vao, vbo, ibo;
        const Application& Application = Application::GetCurrentApplication();
        const Window& Window = Application.GetWindow();
        const float Width = (float)Window.GetWidth();
        const float Height = (float)Window.GetHeight();
        
        const float X0 = Math::Map(Rect.X, 0.0f, Width, -1.0f, 1.0f);
        const float Y0 = -Math::Map(Rect.Y, 0.0f, Height, -1.0f, 1.0f);
        const float X1 = Math::Map(Rect.X + Rect.Width, 0.0f, Width, -1.0f, 1.0f);
        const float Y1 = -Math::Map(Rect.Y, 0.0f, Height, -1.0f, 1.0f);
        const float X2 = Math::Map(Rect.X + Rect.Width, 0.0f, Width, -1.0f, 1.0f);
        const float Y2 = -Math::Map(Rect.Y + Rect.Height, 0.0f, Height, -1.0f, 1.0f);
        const float X3 = Math::Map(Rect.X, 0.0f, Width, -1.0f, 1.0f);
        const float Y3 = -Math::Map(Rect.Y + Rect.Height, 0.0f, Height, -1.0f, 1.0f);
        
        const Vertex vertices[4]
        {
            { { X0, Y0, 0.0f}, HYDRO_NO_UV_NO_NRM, Color },
            { { X1, Y1, 0.0f}, HYDRO_NO_UV_NO_NRM, Color },
            { { X2, Y2, 0.0f}, HYDRO_NO_UV_NO_NRM, Color },
            { { X3, Y3, 0.0f}, HYDRO_NO_UV_NO_NRM, Color },
        };

        const uint32_t indices[6]
        {
            0, 1, 2, 0, 2, 3
        };
        
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glCreateBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);
        
        glCreateBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, Position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, TextureCoordinate));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, Normal));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, Color));
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void OpenGLRendererBackend::DrawCircle(const Rectangle& Rect, float Radius, const Color& Color)
    {
        uint32_t vao, vbo, ibo;
        const Application& Application = Application::GetCurrentApplication();
        const Window& Window = Application.GetWindow();
        const float Width = (float)Window.GetWidth();
        const float Height = (float)Window.GetHeight();


        const float X0 = Math::Map(Rect.X, 0.0f, Width, -1.0f, 1.0f);
        const float Y0 = -Math::Map(Rect.Y, 0.0f, Height, -1.0f, 1.0f);
        const float X1 = Math::Map(Rect.X + Rect.Width, 0.0f, Width, -1.0f, 1.0f);
        const float Y1 = -Math::Map(Rect.Y, 0.0f, Height, -1.0f, 1.0f);
        const float X2 = Math::Map(Rect.X + Rect.Width, 0.0f, Width, -1.0f, 1.0f);
        const float Y2 = -Math::Map(Rect.Y + Rect.Height, 0.0f, Height, -1.0f, 1.0f);
        const float X3 = Math::Map(Rect.X, 0.0f, Width, -1.0f, 1.0f);
        const float Y3 = -Math::Map(Rect.Y + Rect.Height, 0.0f, Height, -1.0f, 1.0f);
        
        const Vertex vertices[4]
        {
            { { X0, Y0, 0.0f}, { 0.0f, 1.0f}, HYDRO_NO_NRM, Color },
            { { X1, Y1, 0.0f}, { 1.0f, 1.0f}, HYDRO_NO_NRM, Color },
            { { X2, Y2, 0.0f}, { 1.0f, 0.0f}, HYDRO_NO_NRM, Color },
            { { X3, Y3, 0.0f}, { 0.0f, 0.0f}, HYDRO_NO_NRM, Color },
        };

        constexpr uint32_t indices[6]
        {
            0, 1, 2, 0, 2, 3
        };
        
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glCreateBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);
        
        glCreateBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, Position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, TextureCoordinate));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, Normal));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Hydro::Vertex, Color));
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void OpenGLRendererBackend::DrawIndexed(const Ref<VertexArray>& VAO, const Ref<VertexBuffer>& VBO,
        const Ref<IndexBuffer>& IBO, const Ref<Shader>& Shader)
    {
        VAO->Bind();
        VBO->Bind();
        IBO->Bind();
        Shader->Bind();
        glDrawElements(GL_TRIANGLES, (GLsizei)IBO->Count(), GL_UNSIGNED_INT, nullptr);
    }


    std::string OpenGLRendererBackend::GetDebugSourceName(uint32_t Source)
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

    Verbosity OpenGLRendererBackend::GetDebugVerbosity(uint32_t Severity)
    {
        switch (Severity)
        {
        case GL_DEBUG_SEVERITY_HIGH: return Error;
        case GL_DEBUG_SEVERITY_MEDIUM:
        case GL_DEBUG_SEVERITY_LOW: return Warning;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
        default: return Trace;
        }
    }
}

