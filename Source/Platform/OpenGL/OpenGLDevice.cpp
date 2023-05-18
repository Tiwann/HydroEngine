#include "HydroPCH.h"
#include "OpenGLDevice.h"

namespace Hydro
{
    OpenGLDevice::OpenGLDevice() : GraphicsDevice()
    {
        Application& application = Application::GetCurrentApplication();
        glfwMakeContextCurrent(application.GetWindow().GetNativeWindow());

        if(!gladLoadGL(glfwGetProcAddress))
        {
            std::cerr << "Failed to retrieve OpenGL function pointers!\n";
            throw std::runtime_error("Failed to retrieve OpenGL function pointers!");
        }
        
        const auto Callback = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
        {
            std::cerr << "[OPENGL] ERROR: " << message << '\n';
        };
            
        glDebugMessageCallback(Callback, nullptr);

        m_Handle = (Handle)wglGetCurrentContext();
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
