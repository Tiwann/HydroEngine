#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include "HydroPCH.h"
#include "Function.h"
#include "String.h"
#include "SharedPointer.h"

namespace Hydro
{
    class Image;
    

    class HYDRO_API Window
    {
    public:
        friend class Application;
        
        Window(const String& name, uint32_t width, uint32_t height, bool resizable);
        ~Window();
        
        static Ref<Window> Create(const String& name, uint32_t width, uint32_t height, bool resizable);
        const GLFWwindow* GetNativeWindow() const;
        GLFWwindow* GetNativeWindow();

        // Callbacks //
        void SetCloseCallback(Function<void, GLFWwindow*> function) const;
        void SetResizeCallback(Function<void, GLFWwindow*, int, int> function) const;
        void SetPositionCallback(Function<void, GLFWwindow*, int, int> function) const;
        void SetFocusCallback(Function<void, GLFWwindow*, int> function) const;
        void SetMaximizeCallback(Function<void, GLFWwindow*, int> function) const;
        bool ShouldClose() const;

        const String& GetName() const;
        void SetName(String name);
        void SetNameTemp(const String& name) const;
        void ResetName() const;
        void SetIcon(const String& filepath)const;
        void SetIcon(const Image& image) const;
        void SetIcons(const std::vector<Ref<Image>>& images);
        bool IsResizable() const;

#if defined(HYDRO_PLATFORM_WINDOWS)
        HWND GetWindowsNativeWindow() const;
#endif

        void Destroy() const;
        bool IsValid() const;
    
    private:
        GLFWwindow* m_Handle = nullptr;
        uint32_t m_Width{0}, m_Height{0}, m_PositionX{0}, m_PositionY{0};
        String m_Name;
        bool m_Resizable{false};
        bool m_HasFocus{false};
        bool m_Maximized{false};
        bool m_Minimized{false};
    };
}
