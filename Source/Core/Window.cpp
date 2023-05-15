#include "HydroPCH.h"
#include "Window.h"
#include "Assertion.h"
#include "Image.h"
#include <GLFW/glfw3native.h>


namespace Hydro
{
    Ref<Window> Window::Create(const String& name, uint32_t width, uint32_t height)
    {
        return CreateRef<Window>(name, width, height);
    }
    
    Window::Window(const String& name, uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height), m_Name(name)
    {
        
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        #if defined(HYDRO_PLATFORM_OPENGL)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        #else
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 
        #endif
        
        m_Handle = glfwCreateWindow(width, height, *name, nullptr, nullptr);
        HYDRO_ASSERT(m_Handle != nullptr, "Failed to create window!");
    }
    
    Window::~Window()
    {
        if(m_Handle) glfwDestroyWindow(m_Handle);
    }
    
    void Window::Destroy() const
    {
        if(m_Handle) glfwDestroyWindow(m_Handle);
    }
    
    bool Window::IsValid() const
    {
        return m_Handle;
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
        glfwSetWindowCloseCallback(m_Handle, function.GetRawPointer());
    }
    
    void Window::SetResizeCallback(Function<void, GLFWwindow*, int, int> function) const
    {
        glfwSetWindowSizeCallback(m_Handle, function.GetRawPointer());
    }
    
    void Window::SetPositionCallback(Function<void, GLFWwindow*, int, int> function) const
    {
        glfwSetWindowPosCallback(m_Handle, function.GetRawPointer());
    }
    
    void Window::SetFocusCallback(Function<void, GLFWwindow*, int> function) const
    {
        glfwSetWindowFocusCallback(m_Handle, function.GetRawPointer());
    }
    
    void Window::SetMaximizeCallback(Function<void, GLFWwindow*, int> function) const
    {
        glfwSetWindowMaximizeCallback(m_Handle, function.GetRawPointer());
    }
    
    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Handle);
    }

    const String& Window::GetName() const
    {
        return m_Name;
    }

    void Window::SetIcon(const String& filepath) const
    {
        const Image icon(*filepath);
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

    void Window::MakeOpenGLContextCurrent() const
    {
        #if defined(HYDRO_PLATFORM_OPENGL)
            glfwMakeContextCurrent(m_Handle);
        #else
            #error "Cannot make context current if not using OpenGL!"
        #endif
    }

#if defined(HYDRO_PLATFORM_WINDOWS)
    HWND Window::GetWindowsNativeWindow() const
    {
        return glfwGetWin32Window(m_Handle);
    }
#endif
    
    void Window::SetName(String name)
    {
        m_Name = std::move(name);
        glfwSetWindowTitle(m_Handle, *m_Name);
    }

    void Window::SetNameTemp(const String& name) const
    {
        glfwSetWindowTitle(m_Handle, *name);
    }

    void Window::ResetName() const
    {
        glfwSetWindowTitle(m_Handle, *m_Name);
    }
}
