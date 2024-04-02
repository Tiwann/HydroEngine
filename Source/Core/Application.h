#pragma once
#include "ApplicationConfiguration.h"
#include "SharedPointer.h"
#include "Color.h"
#include "LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Application, "APPLICATION");

namespace Hydro
{
    class RendererBackend;
    class Window;
    class Image;
    class Scene;
    
    class Application
    {
    public:
        Application();
        virtual ~Application();
        
        void Run();
        virtual void OnInit();
        virtual void OnExit();
        virtual void OnUpdate(float Delta);
        
        virtual Ref<Image> GetWindowIcon() const = 0;
        virtual ApplicationConfiguration CreateConfiguration() const = 0;

    public:
        using Super = Application;
        const ApplicationConfiguration& GetConfiguration() const;
        const GraphicsSettings& GetGraphicsSettings() const;
        
        Window& GetWindow() const;
        RendererBackend& GetRenderer() const;
        Scene& GetScene() const;
        static Application& GetCurrentApplication();

        void RequireExit();
        void RequireExitAndRestart();

        void SetClearColor(const Color& Color);
        void SetCursorVisible(bool Visible) const;
   
    private:
        Ref<Window> m_Window;
        Ref<RendererBackend> m_Renderer;
        Ref<Scene> m_Scene;
        
        Color m_ClearColor{Color::Black};
        static Application* s_Instance;
        ApplicationConfiguration m_Configuration;
        bool m_IsRunnning = true;
        float m_FrameStartTime = 0.0f;
        float m_FrameEndTime = 0.0f;
        float m_DeltaTime = 0.0f;

        
    private:
        bool PreInitialize();
    };
}
