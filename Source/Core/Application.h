#pragma once
#include "ApplicationConfiguration.h"
#include "Renderer.h"
#include "Window.h"
#include "SharedPointer.h"
#include "Image.h"
#include "Color.h"
#include "LogCategory.h"
#include <vector>

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Application, "APPLICATION");

namespace Hydro
{
    class HYDRO_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        virtual void OnInit();
        virtual void OnExit();
        virtual void OnUpdate(float delta);
        virtual std::vector<Ref<Image>> LoadWindowIcons() = 0;
        virtual ApplicationConfiguration CreateConfiguration() = 0;

    public:
        using Super = Application;
        const ApplicationConfiguration& GetConfiguration() const;
        const GraphicsSettings& GetGraphicsSettings() const;
        const Window& GetWindow() const;
        Window& GetWindow();
        
        void RequireExit(bool Restart = true);
        static Application& GetCurrentApplication();

        void SetClearColor(const Color& color);
        Renderer& GetRenderer() const;
            
    private:
        Ref<Window> m_Window;
        Ref<Renderer> m_Renderer;
        Color m_ClearColor{Color::Black};
        static Application* s_Instance;
        ApplicationConfiguration m_Configuration;
        bool m_IsRunnning = true;
        float m_FrameStartTime = 0.0f;
        float m_FrameEndTime = 0.0f;
        float m_DeltaTime = 0.0f;
        bool m_OnInit = false;

    protected:
        

    private:
        bool InitCore();
    };
}
