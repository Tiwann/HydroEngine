#pragma once
#include "ApplicationConfiguration.h"
#include "SharedPointer.h"
#include "Color.h"
#include "LogCategory.h"
#include "Scene.h"
#include "Containers/TreeNode.h"
#include "Editor/Menu.h"
#include "ResourceManager/SoundManager.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Application, "APPLICATION");

namespace Hydro
{
    class ApplicationConfigurationSerializer;
    class TextureManager;
    class ShaderManager;
    class RendererBackend;
    class Window;
    class Image;
    class Scene;
    class GameObject;
    class AudioEngine;
    class ViewportPanel;
    class DetailsPanel;
    class SceneHierarchyPanel;
    class PhysicsSettingsPanel;


    struct ApplicationDelegates
    {
        static inline MulticastDelegate<void()> OnInitEvent;
        static inline MulticastDelegate<void()> OnStartEvent;
        static inline MulticastDelegate<void()> OnStopEvent;
        static inline MulticastDelegate<void()> OnExit;
        static inline MulticastDelegate<void()> OnFrameBegin;
        static inline MulticastDelegate<void()> OnFrameEnd;
    };
    
    class Application
    {
    public:
        using Super = Application;
        
        Application();
        virtual ~Application() = default;
        
        void Run();

        /* Application Interface */
        virtual void OnInit();
        virtual void OnLoadResources(Ref<ShaderManager> ShaderManager, Ref<TextureManager> TextureManager, Ref<SoundManager> SoundManager);
        virtual void OnStart();
        virtual void OnExit();
        virtual void OnRender(const Ref<RendererBackend>& Renderer);
        virtual void OnUpdate(float Delta);
        virtual void OnGui();

        bool SaveSceneAs(const Path& Filepath);
        bool OpenScene(const Path& Filepath);

        virtual ApplicationConfiguration CreateConfiguration(ApplicationConfigurationSerializer& Serializer) const = 0;
        
        const ApplicationConfiguration& GetConfiguration() const;
        const GraphicsSettings& GetGraphicsSettings() const;
        
        const Ref<Window>& GetWindow() const;
        const Ref<RendererBackend>& GetRendererBackend() const;
        const Ref<Scene>& GetScene();
        const Ref<AudioEngine>& GetAudioEngine() const;
        
        static Application& GetCurrentApplication();

        ShaderManager& GetShaderManager();
        TextureManager& GetTextureManager();
        
        void RequireExit();
        void RequireExitAndRestart();

        void SetClearColor(const Color& Color);
        void SetCursorVisible(bool Visible) const;
        
        template<typename T = GameObject, typename = std::enable_if_t<std::is_base_of_v<GameObject, T>>>
        Ref<T> CreateObject(const std::string& Name) const
        {
            return m_Scene->CreateObject<T>(Name);
        }

        Ref<GameObject> CreateCamera() const;
        Ref<GameObject> CreateSprite() const;
        
    private:
        /* Core Components */
        Ref<Window> m_Window;
        Ref<RendererBackend> m_Renderer;
        Ref<Scene> m_Scene;
        Ref<AudioEngine> m_AudioEngine;
        
    protected:
        /* Resources Managers */
        Ref<ShaderManager> m_ShaderManager;
        Ref<TextureManager> m_TextureManager;
        Ref<SoundManager> m_SoundManager;
    private:

        /* UI Components */
        TreeNode<MenuItem> m_MenuBar;
        Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
        Ref<DetailsPanel> m_DetailsPanel;
        Ref<ViewportPanel> m_ViewportPanel;
        Ref<PhysicsSettingsPanel> m_PhysicsSettingsPanel;

    public:
        Ref<SceneHierarchyPanel> GetSceneHierarchyPanel() const;
        Ref<DetailsPanel> GetDetailsPanel() const;
        Ref<ViewportPanel> GetViewportPanel() const;

    private:
        static Application* s_Instance;
        Color m_ClearColor{Color::Black};
        ApplicationConfiguration m_Configuration;
        bool m_IsRunning = true;
        bool m_Start = false;
        bool m_ShowImGuiDemoWindow = false;
        float m_DeltaTime = 0.0f;
        
        bool PreInitialize();
    };
}
