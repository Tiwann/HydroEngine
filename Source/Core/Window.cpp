#include "HydroPCH.h"
#include "Window.h"
#include "Image.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>


namespace Hydro
{
    Ref<Window> Window::Create(const std::string& name, uint32_t width, uint32_t height, bool resizable)
    {
        return CreateRef<Window>(name, width, height, resizable);
    }
    
    Window::Window(const std::string& name, uint32_t width, uint32_t height, bool resizable)
        : m_Width(width), m_Height(height), m_Name(name), m_Resizable(resizable)
    {
        
        glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        #if defined(HYDRO_PLATFORM_OPENGL)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    
    void Window::SetCloseCallback(Function<void, GLFWwindow*> function) const
    {
        glfwSetWindowCloseCallback(m_Handle, function);
    }
    
    void Window::SetResizeCallback(Function<void, GLFWwindow*, int, int> function) const
    {
        glfwSetWindowSizeCallback(m_Handle, function);
    }
    
    void Window::SetPositionCallback(Function<void, GLFWwindow*, int, int> function) const
    {
        glfwSetWindowPosCallback(m_Handle, function);
    }
    
    void Window::SetFocusCallback(Function<void, GLFWwindow*, int> function) const
    {
        glfwSetWindowFocusCallback(m_Handle, function);
    }
    
    void Window::SetMaximizeCallback(Function<void, GLFWwindow*, int> function) const
    {
        glfwSetWindowMaximizeCallback(m_Handle, function);
    }

    void Window::SetIconifyCallback(Function<void, GLFWwindow*, int> function) const
    {
        glfwSetWindowIconifyCallback(m_Handle, function);
    }

    void Window::SetKeyCallback(Function<void, GLFWwindow*, int, int, int, int> function) const
    {
        glfwSetKeyCallback(m_Handle, function);
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle);
    }

    bool Window::IsValid() const
    {
        return m_Handle;
    }

    uint32_t Window::GetWidth() const
    {
        return m_Width;
    }

    uint32_t Window::GetHeight() const
    {
        return m_Height;
    }

    const std::string& Window::GetName() const
    {
        return m_Name;
    }

    void Window::SetIcon(const std::string& filepath) const
    {
        const Image icon(filepath.c_str());
        const GLFWimage glfw_image{(int)icon.GetWidth(), (int)icon.GetHeight(), (uint8_t*)icon.GetData()};
        glfwSetWindowIcon(m_Handle, 1, &glfw_image);
    }
    
    void Window::SetIcon(const Image& image) const
    {
        const GLFWimage glfw_image{(int)image.GetWidth(), (int)image.GetHeight(), (uint8_t*)image.GetData()};
        glfwSetWindowIcon(m_Handle, 1, &glfw_image);
    }

    void Window::SetIcons(const std::vector<Ref<Image>>& images)
    {
        std::vector<GLFWimage> glfwImages;
        for (const auto& icon : images)
        {
            GLFWimage image{};
            image.width = icon->GetWidth();
            image.height = icon->GetHeight();
            image.pixels = (uint8_t*)icon->GetData();
            glfwImages.push_back(image);
        }

        glfwSetWindowIcon(m_Handle, (int)glfwImages.size(), glfwImages.data());
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
