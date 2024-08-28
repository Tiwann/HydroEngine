#include "Application.h"
#include "Window.h"
#include "Image.h"
#include "Log.h"
#include "Time.h"
#include "Color.h"
#include "RendererBackend.h"
#include "LogVerbosity.h"
#include "Cursors.h"
#include "Scene.h"
#include "FrameBuffer.h"
#include "CameraSettings.h"
#include "CullMode.h"
#include "MemoryData.h"
#include "ScopedTimer.h"
#include "ResourceManager/ShaderManager.h"
#include "ResourceManager/TextureManager.h"
#include "Audio/AudioSystem.h"
#include "Input/Input.h"
#include "Platform/PlatformImGui.h"
#include "Components/Camera.h"
#include "Components/Rendering/SpriteRenderer.h"
#include "Editor/DetailsPanel.h"
#include "Editor/SceneHierarchyPanel.h"
#include "Editor/ViewportPanel.h"
#include "Editor/PhysicsSettingsPanel.h"
#include "Editor/EditorGUI.h"
#include "Editor/Selection.h"
#include "Serialization/ApplicationConfigurationSerializer.h"
#include "Serialization/SceneSerializer.h"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Hydro
{
    extern bool g_ApplicationRunning;

    Application::Application(Array<const char*> Arguments) : m_Arguments(std::move(Arguments))
    {
    }

    void Application::OnInit()
    {
        m_ShaderManager->Load("Sprite",         "Engine/Assets/Shaders/Sprite.glsl");
        m_ShaderManager->Load("UniformColor",   "Engine/Assets/Shaders/UniformColor.glsl");
        m_ShaderManager->Load("Circle",         "Engine/Assets/Shaders/Circle.glsl");
        
        m_Scene = CreateRef<Scene>();
        m_Scene->SetName("Default Scene");
        m_Scene->OnInit();

        m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene.get());
        m_DetailsPanel = CreateRef<DetailsPanel>(m_Scene.get());
        m_ViewportPanel = CreateRef<ViewportPanel>();
        m_PhysicsSettingsPanel = CreateRef<PhysicsSettingsPanel>();
        
        m_DetailsPanel->OnInit();
        m_SceneHierarchyPanel->OnInit();
        m_ViewportPanel->OnInit();
        m_PhysicsSettingsPanel->OnInit();

        static const char* HydroSceneFilter = "Hydro Engine Scene (.htscn)\0*.htscn\0\0";
        auto& File = m_MenuBar.AddChild({ "File" });
        File.AddChild({ "Open Scene" , nullptr, [this]
        {
            const Path Filepath = File::OpenFileDialog("Open Scene", "", HydroSceneFilter);
            OpenScene(Filepath);
        }});
        File.AddChild({ "Save Scene" });
        File.AddChild({ "Save Scene As", nullptr, [this]
        {
            const Path Filepath = File::SaveFileDialog("Save scene as...", "", HydroSceneFilter);
            SaveSceneAs(Filepath);
        }});
        File.AddChild({ "Exit", nullptr, [this]{ RequireExit(); } });

        auto& Edit = m_MenuBar.AddChild({ "Edit" });
        Edit.AddChild({ "Undo" });
        Edit.AddChild({ "Redo" });
        Edit.AddChild({ "Preferences" });

        
        auto& View = m_MenuBar.AddChild({ "View" });
        View.AddChild({ "Details Panel", m_DetailsPanel->OpenedPtr() });
        View.AddChild({ "Scene Hierarchy", m_SceneHierarchyPanel->OpenedPtr() });
        View.AddChild({ "Viewport Window", m_ViewportPanel->OpenedPtr() });
        View.AddChild({ "Physics Settings", m_PhysicsSettingsPanel->OpenedPtr() });
        View.AddChild({ "ImGui Demo Window" , &m_ShowImGuiDemoWindow});

        auto& Scene = m_MenuBar.AddChild({ "Scene"});
        Scene.AddChild({ "Rename" });
        Scene.AddChild({ "Create Entity", nullptr, [this]
        {
            const Ref<class Entity> Entity = CreateEntity("New Entity");
            Selection::SetEntity(Entity);
        }});
        Scene.AddChild({ "Create Camera", nullptr, [this]
        {
            const Ref<class Entity> Camera = CreateCamera();
            Selection::SetEntity(Camera);
        }});
        
        auto& Misc = m_MenuBar.AddChild({ "Misc" });
        auto& Shaders = Misc.AddChild({ "Shaders" });
        Shaders.AddChild({ "Reload All", nullptr, [this]
        {
            m_ShaderManager->ReloadAll();
        }});
        
        
        ApplicationDelegates::OnInitEvent.Broadcast();
        OnLoadResources(m_ShaderManager, m_TextureManager, m_SoundManager);
    }

    

    void Application::Run()
    {
        if(!PreInitialize())
        {
            HYDRO_LOG(Application, Verbosity::Error, "Failed to init Hydro Framework Core!");
            RequireExit();
            return;
        }

        m_Window->Show();
        OnInit();
        
        while(m_IsRunning)
        {
            ApplicationDelegates::OnFrameBegin.Broadcast();
            Input::ResetInputStates();
            glfwPollEvents();
            ScopedTimer FrameTimer([this](const float Duration) { m_DeltaTime = Duration; });
            
            OnUpdate(m_DeltaTime * Time::Scale);
            OnRender(m_Renderer);
            
            if(m_Configuration.WithEditor)
            {
                UI::BeginFrame();
                DockNodeFlags Flags = DockNodeFlagBit::PassthruCentralNode;
                ImGui::DockSpaceOverViewport(ImGui::GetID("Dockspace"), ImGui::GetMainViewport(), Flags.As<ImGuiDockNodeFlags>());
                OnGui();
                UI::EndFrame();
                UI::Draw();
            }
            
            m_Renderer->SwapBuffers();
            ApplicationDelegates::OnFrameEnd.Broadcast();
        }
        
        OnExit();
    }

    void Application::OnLoadResources(Ref<ShaderManager> ShaderManager, Ref<TextureManager> TextureManager, Ref<SoundManager> SoundManager)
    {
    }

    void Application::OnStart()
    {
        m_Scene->ForEach([](const Ref<Entity>& Entity)
        {
            Entity->OnStart();
        });
    }

    
    void Application::OnRender(const Ref<RendererBackend>& Renderer)
    {
        if(m_Configuration.WithEditor)
        {
            if(!m_ViewportPanel->IsAvailable()) return;
            Renderer->ClearColorBuffer(m_ClearColor.WithOpacity(1.0f));
            m_ViewportPanel->GetFrameBuffer()->Bind();

            if(m_Renderer->GetCurrentCamera())
                m_Renderer->GetCurrentCamera()->Settings.SetDimensions(m_ViewportPanel->GetSize()); // Temp
            Renderer->SetViewportRect(Vector2::Zero, m_ViewportPanel->GetSize());
            Renderer->ClearColorBuffer({0.08f, 0.08f, 0.08f, 1.0f});
            m_Scene->OnRender(Renderer);
            m_ViewportPanel->GetFrameBuffer()->Unbind();
        }
        else
        {
            Renderer->ClearColorBuffer(m_ClearColor.WithOpacity(1.0f));
            m_Scene->OnRender(Renderer);
        }
    }

    static void UpdateWindowName(float Delta, const Application* Application)
    {
        std::string NewWindowName = Application->GetWindow()->GetName();
        if(Application->GetConfiguration().ShowDeltaTime)
        {
            NewWindowName.append(fmt::format(" | DeltaTime: {}", Delta));
        }

        if(Application->GetConfiguration().ShowFPS)
        {
            const uint32_t FPS = (uint32_t)(1.0f / Delta);
            NewWindowName.append(fmt::format(" FPS: {}", FPS));
        }
        Application->GetWindow()->SetNameTemp(NewWindowName);
    }
    
    void Application::OnUpdate(float Delta)
    {     
        if(m_Configuration.ShowDeltaTime || m_Configuration.ShowFPS)
        {
            if(m_Configuration.WindowTitleUpdateTime != 0.0f)
            {
                static float Timer = 0.0f;
                Timer += Delta / Time::Scale;
                if(Timer >= m_Configuration.WindowTitleUpdateTime)
                {
                    Timer = 0.0f;
                    UpdateWindowName(Delta / Time::Scale, this);
                }
            }
            else
            {
                UpdateWindowName(Delta / Time::Scale, this);
            }
        }

        m_AudioSystem.OnUpdate();
        m_Scene->OnUpdate(Delta);
        m_DetailsPanel->OnUpdate(Delta);
        m_SceneHierarchyPanel->OnUpdate(Delta);
        m_ViewportPanel->OnUpdate(Delta);
    }

    
    void Application::OnGui()
    {
        const ImGuiIO& IO = ImGui::GetIO();

        UI::MainMenuMenuBar(m_MenuBar);
        m_DetailsPanel->OnInspectorGUI(IO);
        m_ViewportPanel->OnInspectorGUI(IO);
        m_SceneHierarchyPanel->OnInspectorGUI(IO);
        m_PhysicsSettingsPanel->OnInspectorGUI(IO);
        
        if(m_ShowImGuiDemoWindow) ImGui::ShowDemoWindow(&m_ShowImGuiDemoWindow);
    }

    void Application::OnExit()
    {
        m_Scene->OnDestroy();

        if(m_Configuration.WithEditor)
            UI::Shutdown();
        
        m_TextureManager->UnloadAll();
        m_ShaderManager->UnloadAll();
        m_SoundManager->UnloadAll();
        
        m_AudioSystem.Destroy();
        m_Renderer->Destroy();
        m_Window->Destroy();
        
        glfwTerminate();
        ApplicationDelegates::OnExit.Broadcast();
    }

    bool Application::SaveSceneAs(const Path& Filepath)
    {
        SceneSerializer Serializer;
        return Serializer.Serialize(m_Scene, Filepath);
    }

    bool Application::OpenScene(const Path& Filepath)
    {
        return false;
    }


    const ApplicationConfiguration& Application::GetConfiguration() const
    {
        return m_Configuration;
    }

    const GraphicsSettings& Application::GetGraphicsSettings() const
    {
        return m_Configuration.Graphics;
    }


    const Ref<Window>& Application::GetWindow() const
    {
        return m_Window;
    }

    void Application::RequireExit()
    {
        HYDRO_LOG(Application, Verbosity::Warning, "Exit required. Cleaning...");
        m_IsRunning = false;
        g_ApplicationRunning = false;
    }

    void Application::RequireExitAndRestart()
    {
        HYDRO_LOG(Application, Verbosity::Warning, "Exit required. Cleaning... Application will restart");
        m_IsRunning = false;
        g_ApplicationRunning = true;
    }
    
    ShaderManager& Application::GetShaderManager()
    {
        return *m_ShaderManager;
    }

    TextureManager& Application::GetTextureManager()
    {
        return *m_TextureManager;
    }

    void Application::SetClearColor(const Color& color)
    {
        m_ClearColor = color;
    }

    void Application::SetCursorVisible(bool Visible) const
    {
        Cursor::SetCursorVisible(m_Window, Visible);
    }

    Ref<Entity> Application::CreateCamera() const
    {
        const CameraSettings Settings = CameraSettings::DefaultOrthographic
        .WithDimension(GetWindow()->GetWidth(), GetWindow()->GetHeight());
        const auto& CameraObj = CreateEntity("Camera");
        const auto& Cam = CameraObj->AddComponent<Camera>();
        Cam->Settings = Settings;
        m_Renderer->SetCurrentCamera(Cam);
        return CameraObj;
    }

    Ref<Entity> Application::CreateSprite() const
    {
        const auto& NewEntity = CreateEntity("New Sprite");
        const auto& SpriteRend = NewEntity->AddComponent<SpriteRenderer>();

        return NewEntity;
    }

    const Ref<RendererBackend>& Application::GetRendererBackend() const
    {
        return m_Renderer;
    }

    const Ref<Scene>& Application::GetScene()
    {
        return m_Scene;
    }

    const AudioSystem& Application::GetAudioSystem() const
    {
        return m_AudioSystem;
    }

    AudioSystem& Application::GetAudioSystem()
    {
        return m_AudioSystem;
    }

    Ref<SceneHierarchyPanel> Application::GetSceneHierarchyPanel() const
    {
        return m_SceneHierarchyPanel;
    }

    Ref<DetailsPanel> Application::GetDetailsPanel() const
    {
        return m_DetailsPanel;
    }

    Ref<ViewportPanel> Application::GetViewportPanel() const
    {
        return m_ViewportPanel;
    }

    bool Application::PreInitialize()
    {
        // Init spdlog logger
        Log::Init();
        
        // Init GLFW
        if(!glfwInit())
        {
            HYDRO_LOG(Application, Verbosity::Error, "Failed to initilaize glfw!");
            return false;
        }
        
        HYDRO_LOG(Application, Verbosity::Info, "Using GLFW version {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

        glfwSetErrorCallback([](int code, const char* message)
        {
            HYDRO_LOG(Application, Verbosity::Warning, "[GLFW] Error {}: {}", code, message);
        });
        
        // Create Window, set its close callback
        HYDRO_LOG(Application, Verbosity::Trace, "Creating window...");

        ApplicationConfigurationSerializer Serializer;
        m_Configuration = CreateConfiguration(Serializer);
        
        if(m_Configuration.ShowGraphicsAPIName) m_Configuration.AppName = fmt::format("{} | {}", m_Configuration.AppName, HYDRO_RHI_NAME);
        if(m_Configuration.ShowOSName) m_Configuration.AppName = fmt::format("{} {}", m_Configuration.AppName, HYDRO_OS_NAME);
        if(m_Configuration.ShowConfiguration) m_Configuration.AppName = fmt::format("{}", m_Configuration.AppName, HYDRO_CONFIG_NAME);
        m_Window = Window::Create(m_Configuration.AppName, m_Configuration.WindowWidth, m_Configuration.WindowHeight, m_Configuration.WindowResizable);

        if(File::Exists(m_Configuration.IconPath))
        {
            const Ref<Image> Icon = Image::Create(m_Configuration.IconPath, ImageFormat::RGBA8);
            m_Window->SetIcon(Icon);
        } else
        {
            HYDRO_LOG(Application, Verbosity::Warning, "Failed to load custom window icon! Loading default from memory.");
            using namespace MemoryData;
            const BufferView DefaultIconData(HydroEngineLogo, std::size(HydroEngineLogo));
            const Ref<Image> DefaultIcon = Image::Create(DefaultIconData, ImageFormat::RGBA8);
            m_Window->SetIcon(DefaultIcon);
        }
        
        glfwSetWindowUserPointer(m_Window->GetNativeWindow(), this);
        // Set window callbacks
        glfwSetWindowCloseCallback(m_Window->GetNativeWindow(), [](GLFWwindow*)
        {
            g_Application->RequireExit();
        });

        glfwSetWindowFocusCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int focus){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_HasFocus = (bool)focus;
#if defined(HYDRO_LOG_WINDOW_CALLBACKS)
            const std::string message = focus ? "Window focused" : "Window unfocused";
            HYDRO_LOG(Application, Verbosity::Trace, "[WINDOW] {}", message);
#endif
        });

        glfwSetWindowMaximizeCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int maximized){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Maximized = (bool)maximized;
#if defined(HYDRO_LOG_WINDOW_CALLBACKS)
            if(maximized) HYDRO_LOG(Application, Verbosity::Trace, "[WINDOW] maximized");
#endif
        });

        glfwSetWindowPosCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int x, int y){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_PositionX = x;
            application->m_Window->m_PositionY = y;
        });

        glfwSetWindowSizeCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int width, int height){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Width = width;
            application->m_Window->m_Height = height;
            #if defined(HYDRO_PLATFORM_OPENGL)
            glViewport(0, 0, width, height);
            #endif
        });

        glfwSetWindowIconifyCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int iconified)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Minimized = (bool)iconified;
#if defined(HYDRO_LOG_WINDOW_CALLBACKS)
            if(iconified) HYDRO_LOG(Application, Verbosity::Trace, "[WINDOW] minimized");
#endif
        });

        glfwSetFramebufferSizeCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int width, int height)
        {
            #if defined(HYDRO_PLATFORM_OPENGL)
            glViewport(0, 0, width, height);
            #endif
        });
        
        glfwSetKeyCallback(m_Window->GetNativeWindow(), [](GLFWwindow* window, int key, int, int action, int)
        {
            const Application* App = (Application*)glfwGetWindowUserPointer(window);
            Window::KeyDelegate& OnKeyEvent = App->GetWindow()->OnKeyEvent;
            
            switch (action)
            {
            case GLFW_PRESS:
                if(OnKeyEvent.IsBound()) OnKeyEvent.Broadcast((KeyCode)key, InputState::Pressed);
                Input::s_KeyStates[(KeyCode)key] = InputState::Pressed;
                break;
            case GLFW_RELEASE:
                if(OnKeyEvent.IsBound()) OnKeyEvent.Broadcast((KeyCode)key, InputState::Released);
                Input::s_KeyStates[(KeyCode)key] = InputState::Released;
                break;
            }
        });

        glfwSetMouseButtonCallback(m_Window->GetNativeWindow(), [](GLFWwindow *window, int button, int action, int)
        {
            const Application* App = (Application*)glfwGetWindowUserPointer(window);
            Window::MouseButtonDelegate& OnMouseButtonEvent = App->GetWindow()->OnMouseButtonEvent;
            switch (action)
            {
            case GLFW_PRESS:
                if(OnMouseButtonEvent.IsBound()) OnMouseButtonEvent.Broadcast((MouseButton)button, InputState::Pressed);
                Input::s_MouseButtonStates[(MouseButton)button] = InputState::Pressed;
                break;
            case GLFW_RELEASE:
                if(OnMouseButtonEvent.IsBound()) OnMouseButtonEvent.Broadcast((MouseButton)button, InputState::Released);
                Input::s_MouseButtonStates[(MouseButton)button] = InputState::Released;
                break;
            }
        });
        
        
        HYDRO_LOG(Application, Verbosity::Info, "Window successfully created!");
        
        
        if(!m_Window->IsValid())
        {
            HYDRO_LOG(Application, Verbosity::Error, "Failed to create window!");
            return false;
        }

        HYDRO_LOG(Application, Verbosity::Trace, "Creating Renderer...");
        
        m_Renderer = RendererBackend::Create(this);
        if(!m_Renderer->Initialize())
        {
            HYDRO_LOG(Application, Verbosity::Error, "Failed to create renderer!");
            return false;
        }
        m_Renderer->SetCullMode(CullMode::BackFace);
        HYDRO_LOG(Application, Verbosity::Info, "Renderer created!");

        
        if(!m_AudioSystem.Init(44100, 1024))
        {
            HYDRO_LOG(Application, Verbosity::Error, "Failed to create audio engine!");
            return false;
        }

        m_ShaderManager = CreateRef<ShaderManager>();
        m_TextureManager = CreateRef<TextureManager>();
        m_SoundManager = CreateRef<SoundManager>();
        

        if(m_Configuration.WithEditor)
        {
            if(!UI::Init(this))
                return false;
        }
        
        return true;
    }
}
