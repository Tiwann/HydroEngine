#pragma once
#include "HydroPCH.h"
#include "Core/Application.h"
#include "Platform/GraphicsDevice.h"

namespace Hydro
{
    class HYDRO_API OpenGLDevice : public GraphicsDevice
    {
    public:
        OpenGLDevice(Application& application) : GraphicsDevice(application)
        {
            m_Application.GetWindow().MakeOpenGLContextCurrent();

            if(!gladLoadGL(glfwGetProcAddress))
            {
                std::cerr << "Failed to retrieve OpenGL function pointers!\n";
                throw std::runtime_error("Failed to retrieve OpenGL function pointers!");
            }
            
            const auto Callback = Function<void, GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*, const void*>([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
            {
                std::cerr << "[OPENGL] ERROR: " << message << '\n';
            });
            
            glDebugMessageCallback(Callback, nullptr);

            m_Handle = (Handle)wglGetCurrentContext();
        }

        void ClearDepthBuffer() override
        {
            glClear(GL_DEPTH_BUFFER_BIT);
        }
        void ClearColor(Color color) override
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(color.r, color.g, color.b, color.a);
        }

        void SwapBuffers() override
        {
            glfwSwapBuffers(m_Application.GetWindow().GetNativeWindow());
        }
    };
}
