#pragma once
#include "SharedPointer.h"
#include "LogCategory.h"
#include "NumericTypes.h"
#include <string>


struct GLFWwindow;

namespace Hydro
{
    class Image;
    class Vector2;
    
    HYDRO_DECLARE_LOG_CATEGORY_STATIC(Input, "INPUT")
    
    class Window
    {
    public:
        friend class Application;
        
        Window(const std::string& name, u32 width, u32 height, bool resizable);
        ~Window();
        


        static Ref<Window> Create(const std::string& name, u32 width, u32 height, bool resizable);
        const GLFWwindow* GetNativeWindow() const;
        GLFWwindow* GetNativeWindow();
        
        bool ShouldClose() const;
        bool IsValid() const;

        template<typename T = f32, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        T GetWidth() const
        {
            return static_cast<T>(m_Width);
        }

        template<typename T = f32, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
        T GetHeight() const
        {
            return static_cast<T>(m_Height);
        }

        Vector2 GetSize() const;
        Vector2 GetCenter() const;
        
        const std::string& GetName() const;
        void SetName(std::string name);
        void SetNameTemp(const std::string& name) const;
        void ResetName() const;
        void SetIcon(const std::string& filepath)const;
        void SetIcon(const Ref<Image>& image) const;
        bool IsResizable() const;
        void Destroy();

        void Show() const;
        void Hide() const;

        bool IsVisible() const { return m_Visible; }

        
    private:
        GLFWwindow* m_Handle = nullptr;
        u32 m_Width{0}, m_Height{0}, m_PositionX{0}, m_PositionY{0};
        std::string m_Name;
        bool m_Resizable{false};
        bool m_HasFocus{false};
        bool m_Maximized{false};
        bool m_Minimized{false};
        bool m_Visible{true};
    };
}
