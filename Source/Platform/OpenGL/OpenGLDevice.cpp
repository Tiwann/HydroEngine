#include "HydroPCH.h"
#include "OpenGLDevice.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "Core/Color.h"
#include <GLFW/glfw3.h>

#include "Core/LogVerbosity.h"


namespace Hydro
{
    OpenGLDevice::OpenGLDevice() : RendererDevice()
    {
        Application& application = Application::GetCurrentApplication();
        HYDRO_LOG(OpenGL, Verbosity::Trace, "Creating OpenGL context");
        glfwMakeContextCurrent(application.GetWindow().GetNativeWindow());
        glfwSwapInterval(true);
        
        if(!gladLoadGL(glfwGetProcAddress))
        {
            HYDRO_LOG(OpenGL, Verbosity::Error, "Failed to retrieve OpenGL function pointers!");
            application.RequireExit(false);
            return;
        }
        
        const auto Callback = [](GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei, const GLchar *Message, const void * UserParams)
        {
            const Verbosity Verbo = GetDebugVerbosity(Severity);
            const std::string SourceName = GetDebugSourceName(Source);
            HYDRO_LOG(OpenGL, Verbo, "Debug ({}): {}", SourceName, Message);
            
            if(Type == GL_DEBUG_TYPE_ERROR)
            {
                //HYDRO_BREAK();
            }
        };
        glDebugMessageCallback(Callback, nullptr);
        glEnable(GL_FRAMEBUFFER_SRGB);

        std::string Renderer = (const char*)glGetString(GL_RENDERER);
        HYDRO_LOG(OpenGL, Info, "Using OpenGL 4.6");
        HYDRO_LOG(OpenGL, Info, "Using GPU: {}", Renderer);
        m_IsReady = true;
    }

    void OpenGLDevice::ClearDepthBuffer()
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLDevice::ClearColor(const Color& color)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLDevice::SwapBuffers()
    {
        glfwSwapBuffers(Application::GetCurrentApplication().GetWindow().GetNativeWindow());
    }

    void OpenGLDevice::DrawIndexed()
    {
        
    }

    std::string OpenGLDevice::GetDebugSourceName(uint32_t Source)
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

    Verbosity OpenGLDevice::GetDebugVerbosity(uint32_t Severity)
    {
        switch (Severity)
        {
        case GL_DEBUG_SEVERITY_HIGH: return Error;
        case GL_DEBUG_SEVERITY_MEDIUM: return Warning;
        case GL_DEBUG_SEVERITY_LOW: return Warning;
        case GL_DEBUG_SEVERITY_NOTIFICATION: return Trace;
        default: return Trace;
        }
    }
}

