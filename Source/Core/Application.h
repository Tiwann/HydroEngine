#pragma once
#include "ApplicationConfiguration.h"
#include "SharedPointer.h"
#include "Color.h"
#include "LogCategory.h"
#include "Scene.h"
#include "Containers/TreeNode.h"
#include "Editor/Menu.h"
#include "ResourceManager/SoundManager.h"
#include "Audio/AudioSystem.h"
#include "Input/GamepadButton.h"
#include "Input/InputState.h"
#include "Input/KeyCode.h"
#include "Input/MouseButton.h"
#include "Core/Containers/String.h"

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
    class Entity;
    class AudioSystem;
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
        static inline MulticastDelegate<void(Path const&)> OnSceneSaveEvent;
        static inline MulticastDelegate<void(Path const&)> OnSceneLoadEvent;

        using KeyDelegate = MulticastDelegate<void(KeyCode, InputState)>;
        static inline KeyDelegate OnKeyEvent;

        using MouseButtonDelegate = MulticastDelegate<void(MouseButton, InputState)>;
        static inline MouseButtonDelegate OnMouseButtonEvent;

        using GamepadButtonDelegate = MulticastDelegate<void(size_t ID, GamepadButton Button, InputState State)>;
        static inline GamepadButtonDelegate OnGamepadButtonEvent;

        using GamepadAxisDelegate = MulticastDelegate<void(size_t ID, size_t Axis, float Value)>;
        static inline GamepadAxisDelegate OnGamepadAxisEvent;
    };
    
    class Application
    {
    public:
        Application(Array<const char*> Arguments);
        virtual ~Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;
        
        void Run();

        /* Application Interface */
        virtual void OnInit();
        virtual void OnLoadResources(Ref<ShaderManager> ShaderManager, Ref<TextureManager> TextureManager, Ref<SoundManager> SoundManager);
        virtual void OnStart();
        virtual void OnExit();
        virtual void OnRender(const Ref<RendererBackend>& Renderer);
        virtual void OnUpdate(f32 Delta);
        virtual void OnGui();

        virtual ApplicationConfiguration CreateConfiguration(ApplicationConfigurationSerializer& Serializer) const = 0;
        
        const ApplicationConfiguration& GetConfiguration() const;
        const GraphicsSettings& GetGraphicsSettings() const;
        
        const Ref<Window>& GetWindow() const;
        const Ref<RendererBackend>& GetRendererBackend() const;
        const Ref<Scene>& GetScene();
        
        const AudioSystem& GetAudioSystem() const;
        AudioSystem& GetAudioSystem();
        
        ShaderManager& GetShaderManager();
        TextureManager& GetTextureManager();
        
        void RequireExit();
        void RequireExitAndRestart();

        void SetClearColor(const Color& Color);
        void SetCursorVisible(bool Visible) const;
        
        template<typename T = Entity, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
        Ref<T> CreateEntity(const String& Name) const
        {
            return m_Scene->CreateEntity<T>(Name);
        }

        Ref<Entity> CreateCamera() const;
        Ref<Entity> CreateSprite() const;
        
    private:
        /* Core Components */
        Ref<Window> m_Window;
        Ref<RendererBackend> m_Renderer;
        Ref<Scene> m_Scene;
        AudioSystem m_AudioSystem;
        
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
        Array<const char*> m_Arguments;
        Color m_ClearColor{Color::Black};
        ApplicationConfiguration m_Configuration;
        bool m_IsRunning = true;
        bool m_Start = false;
        bool m_ShowImGuiDemoWindow = false;
        f32 m_DeltaTime = 0.0f;
        
        bool PreInitialize();
    };

    inline Application* g_Application;
}
