#include "HydroPCH.h"
#include "OpenGLDevice.h"
#include "Core/Application.h"
#include "Core/Log.h"

namespace Hydro
{
    OpenGLDevice::OpenGLDevice() : RendererDevice()
    {
        Application& application = Application::GetCurrentApplication();
        HYDRO_LOG_TRACE("[OPENGL] Creating OpenGL context");
        glfwMakeContextCurrent(application.GetWindow().GetNativeWindow());
        glfwSwapInterval(true);

        if(!gladLoadGL(glfwGetProcAddress))
        {
            HYDRO_LOG_ERROR("[OPENGL] Failed to retrieve OpenGL function pointers!");
            application.RequireExit(false);
            return;
        }
        
        const auto Callback = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
        {
            HYDRO_LOG_ERROR("[OPENGL] Error:\n{}", message);
        };
        glDebugMessageCallback(Callback, nullptr);
        glEnable(GL_FRAMEBUFFER_SRGB);
        
        HYDRO_LOG_INFO("[OPENGL] Using OpenGL 4.6");
        HYDRO_LOG_INFO("[OPENGL] Using GPU: {}", glGetString(GL_RENDERER));
        m_IsReady = true;
    }

    void OpenGLDevice::ClearDepthBuffer()
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLDevice::ClearColor(Color color)
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
}
