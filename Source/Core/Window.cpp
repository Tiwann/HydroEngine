#include "Window.h"
#include "Image.h"
#include "Filesystem.h"
#include "Math/Vector2.h"
#include <GLFW/glfw3.h>
#include <glad/gl.h>


namespace Hydro
{
    Ref<Window> Window::Create(const std::string& name, uint32 width, uint32 height, bool resizable)
    {
        return CreateRef<Window>(name, width, height, resizable);
    }
    
    Window::Window(const std::string& name, uint32 width, uint32 height, bool resizable)
        : m_Width(width), m_Height(height), m_Name(name), m_Resizable(resizable)
    {
        
        glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        #if defined(HYDRO_PLATFORM_OPENGL)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_SAMPLES, 4);
        #if defined(HYDRO_DEBUG)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        #endif
        #else
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 
        #endif
        m_Handle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }
    
    Window::~Window()
    {
        if(m_Handle)
        {
            glfwDestroyWindow(m_Handle);
            m_Handle = nullptr;
        }
    }
    
    void Window::Destroy()
    {
        if(m_Handle)
        {
            glfwDestroyWindow(m_Handle);
            m_Handle = nullptr;
        }
    }

    void Window::Show() const
    {
        glfwShowWindow(m_Handle);
    }

    void Window::Hide() const
    {
        glfwHideWindow(m_Handle);
    }


    const GLFWwindow* Window::GetNativeWindow() const
    {
        return m_Handle;
    }
    
    GLFWwindow* Window::GetNativeWindow()
    {
        return m_Handle;
    }
    
    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle);
    }

    bool Window::IsValid() const
    {
        return m_Handle;
    }


    Vector2 Window::GetSize() const
    {
        return { GetWidth<float>(), GetHeight<float>() };
    }

    Vector2 Window::GetCenter() const
    {
        return { (float)m_Width / 2, (float)m_Height / 2 };
    }

    const std::string& Window::GetName() const
    {
        return m_Name;
    }

    void Window::SetIcon(const std::string& filepath) const
    {
        Buffer ImageData(File::ReadToBuffer(filepath));
        const Image icon(ImageData, ImageFormat::RGBA8);
        const GLFWimage glfw_image{(int)icon.GetWidth(), (int)icon.GetHeight(), (uint8*)icon.GetData()};
        glfwSetWindowIcon(m_Handle, 1, &glfw_image);
        ImageData.Free();
    }
    
    void Window::SetIcon(const Ref<Image>& image) const
    {
        const GLFWimage glfw_image{(int)image->GetWidth(), (int)image->GetHeight(), (uint8*)image->GetData()};
        glfwSetWindowIcon(m_Handle, 1, &glfw_image);
    }
    

    bool Window::IsResizable() const
    {
        return m_Resizable;
    }
    
    void Window::SetName(std::string name)
    {
        m_Name = std::move(name);
        glfwSetWindowTitle(m_Handle, m_Name.c_str());
    }

    void Window::SetNameTemp(const std::string& name) const
    {
        glfwSetWindowTitle(m_Handle, name.c_str());
    }

    void Window::ResetName() const
    {
        glfwSetWindowTitle(m_Handle, m_Name.c_str());
    }
}
