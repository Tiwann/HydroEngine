#include "HydroPCH.h"

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


#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>

#include "CameraSettings.h"
#include "CullMode.h"
#include "MemoryData.h"
#include "TreeNode.h"
#include "ResourceManager/ShaderManager.h"
#include "ResourceManager/TextureManager.h"
#include "Audio/AudioEngine.h"
#include "Input/Input.h"

#include "Platform/PlatformImGui.h"
#include "Components/Camera.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Editor/DetailsPanel.h"
#include "Editor/EditorGUI.h"
#include "Editor/SceneHierarchyPanel.h"
#include "Editor/Selection.h"
#include "Editor/ViewportWindow.h"
#include "imgui/imgui_internal.h"
#include "Serialization/SceneSerializer.h"


namespace Hydro
{
    extern bool g_ApplicationRunning;

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
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
            using namespace std::chrono;
            const auto StartClock = high_resolution_clock::now();
           
            
            /*if(!m_Configuration.WithEditor)
                m_Start = true;

            static bool hasStarted;
            if(m_Start)
            {
                if(hasStarted)
                {
                    OnUpdate(m_DeltaTime * Time::Scale);
                } else
                {
                    OnStart();
                    hasStarted = true;
                    ApplicationDelegates::OnStartEvent.Broadcast();
                }
            }
            else
            {
                if(hasStarted)
                {
                    m_Scene->OnDestroy();
                    m_Scene->OnInit();
                    hasStarted = false;
                    ApplicationDelegates::OnStopEvent.Broadcast();
                }
            }*/
            
            OnUpdate(m_DeltaTime * Time::Scale);
            OnRender(m_Renderer);

            if(m_Configuration.WithEditor)
            {
                UI::BeginFrame();
                DockNodeFlags Flags = DockNodeFlagBit::PassthruCentralNode ;
                ImGui::DockSpaceOverViewport(ImGui::GetID("Dockspace"), ImGui::GetMainViewport(), Flags.As<ImGuiDockNodeFlags>());
    
                if(!m_Window->m_Minimized)
                    OnGui();
                UI::EndFrame();
                UI::Draw();
            }
            
            m_Renderer->SwapBuffers();
            const auto EndClock = high_resolution_clock::now();
            const auto FrameDuration = duration_cast<nanoseconds>(EndClock - StartClock).count();
            m_DeltaTime = (float)FrameDuration / NANOSECONDS;
            ApplicationDelegates::OnFrameEnd.Broadcast();
        }
        
        OnExit();
    }

    void Application::OnInit()
    {
        m_ShaderManager->Load("Sprite", "Engine/Assets/Shaders/Sprite.glsl");
        m_ShaderManager->Load("UniformColor", "Engine/Assets/Shaders/UniformColor.glsl");
        m_ShaderManager->Load("Circle", "Engine/Assets/Shaders/Circle.glsl");

        // m_FrameBuffer = FrameBuffer::Create();
        // m_FrameBufferTexture = Texture2D::Create("Framebuffer", m_Window->GetWidth<uint32_t>(), m_Window->GetHeight<uint32_t>());
        // m_FrameBuffer->AttachTexture(m_FrameBufferTexture, FrameBufferAttachment::Color);
        
        m_Scene = CreateRef<Scene>();
        m_Scene->SetName("Default Scene");
        m_Scene->OnInit();

        m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_Scene.get());
        m_DetailsPanel = CreateRef<DetailsPanel>(m_Scene.get());
        m_ViewportWindow = CreateRef<ViewportWindow>();
        

        m_DetailsPanel->OnInit();
        m_SceneHierarchyPanel->OnInit();
        m_ViewportWindow->OnInit();

        auto& File = m_MenuBar.AddChild({ "File" });
        File.AddChild({ "Open Scene" , nullptr,});
        File.AddChild({ "Save Scene" });
        File.AddChild({ "Save Scene As", nullptr, [this]
        {
            const Path Filepath = File::SaveFileDialog("Save scene as...", "", "Hydro Engine Text Scene (.htscn)\0*.htscn\0\0");
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
        View.AddChild({ "Viewport Window", m_ViewportWindow->OpenedPtr() });
        
        auto& Scene = m_MenuBar.AddChild({ "Scene "});
        Scene.AddChild({ "Rename" });
        auto& GameObject = Scene.AddChild({ "Game Object" });
        GameObject.AddChild({ "Create", nullptr, [this]
        {
            const Ref<class GameObject> Object = CreateObject("New Object");
            Selection::SetGameObject(Object);
        }});

        static bool ShowAllCollisions;
        auto& Misc = m_MenuBar.AddChild({ "Misc" });
        Misc.AddChild({ "Show/Hide Collision", &ShowAllCollisions, [this]
        {
            m_Scene->ForEach([](const Ref<class GameObject>& Object)
            {
                Object->ForEach([](const Ref<Component>& Component)
                {
                   if(Ref<PhysicsComponent> Physics = Cast<PhysicsComponent>(Component))
                   {
                       ShowAllCollisions = !ShowAllCollisions;
                       Physics->SetShowCollisions(ShowAllCollisions);
                   }
                });
            });
        }}); 
        
        ApplicationDelegates::OnInitEvent.Broadcast();
    }

    void Application::OnStart()
    {
        m_Scene->ForEach([](const auto& Object)
        {
            Object->OnStart();
        });
    }

    void Application::OnExit()
    {
        m_Scene->OnDestroy();

        if(m_Configuration.WithEditor)
            UI::Shutdown();

        // m_FrameBuffer->Destroy();
        m_TextureManager->UnloadAll();
        m_ShaderManager->UnloadAll();
        m_SoundManager->UnloadAll();
        
        m_AudioEngine->OnDestroy();
        
        m_Renderer->Destroy();
        m_Window->Destroy();
        glfwTerminate();
        ApplicationDelegates::OnExit.Broadcast();
    }

    void Application::OnRender(const Ref<RendererBackend>& Renderer)
    {
        m_Renderer->ClearDepthBuffer();
        m_Renderer->ClearColorBuffer(m_ClearColor);
        /*if(m_FrameBuffer)
        {
            const Vector2 ViewportSize = m_Viewport->GetSize();
            glViewport(0, 0, (int)ViewportSize.x, (int)ViewportSize.y);
            m_FrameBuffer->Bind();
            
            m_FrameBuffer->Unbind();
        }*/
        m_Scene->OnRender(Renderer);
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

        m_AudioEngine->OnUpdate();
        m_Scene->OnUpdate(Delta);
        m_DetailsPanel->OnUpdate(Delta);
        m_SceneHierarchyPanel->OnUpdate(Delta);
        m_ViewportWindow->OnUpdate(Delta);

        
    }
    
    void Application::OnGui()
    {
        ImGuiIO& IO = ImGui::GetIO();
        
        UI::MenuBar(m_MenuBar);
        
        m_SceneHierarchyPanel->OnInspectorGUI(IO);
        m_DetailsPanel->OnInspectorGUI(IO);
        m_ViewportWindow->OnInspectorGUI(IO);
        
    }

    bool Application::SaveSceneAs(const Path& Filepath)
    {
        if(!File::Exists(Filepath)) File::Create(Filepath);
        SceneSerializer Serializer(Filepath);
        return Serializer.Serialize(*m_Scene);
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
    
    Application& Application::GetCurrentApplication()
    {
        return *s_Instance;
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

    Ref<GameObject> Application::CreateCamera() const
    {
        const CameraSettings Settings = CameraSettings::DefaultOrthographic
        .WithDimension(GetWindow()->GetWidth(), GetWindow()->GetHeight());
        const auto& CameraObj = CreateObject("Camera");
        const auto& Cam = CameraObj->AddComponent<Camera>();
        Cam->Settings = Settings;
        m_Renderer->SetCurrentCamera(Cam);
        return CameraObj;
    }

    const Ref<RendererBackend>& Application::GetRendererBackend() const
    {
        return m_Renderer;
    }

    const Ref<Scene>& Application::GetScene()
    {
        return m_Scene;
    }

    const Ref<AudioEngine>& Application::GetAudioEngine() const
    {
        return m_AudioEngine;
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
        m_Configuration = CreateConfiguration();
        if(m_Configuration.ShowGraphicsAPIName) m_Configuration.AppName = fmt::format("{} | {}", m_Configuration.AppName, HYDRO_RHI_NAME);
        if(m_Configuration.ShowOSName) m_Configuration.AppName = fmt::format("{} {}", m_Configuration.AppName, HYDRO_OS_NAME);
        if(m_Configuration.ShowConfiguration) m_Configuration.AppName = fmt::format("{}", m_Configuration.AppName, HYDRO_CONFIG_NAME);
        m_Window = Window::Create(m_Configuration.AppName, m_Configuration.WindowWidth, m_Configuration.WindowHeight, m_Configuration.WindowResizable);

        if(File::Exists(m_Configuration.IconPath))
        {
            Ref<Image> Icon = Image::Create(m_Configuration.IconPath, ImageFormat::RGBA8);
            m_Window->SetIcon(Icon);
        } else
        {
            HYDRO_LOG(Application, Verbosity::Warning, "Failed to load custom window icon! Loading default from memory.");
            using namespace MemoryData;
            const BufferView DefaultIconData(HydroEngineLogo, std::size(HydroEngineLogo));
            Ref<Image> DefaultIcon = Image::Create(DefaultIconData, ImageFormat::RGBA8);
            m_Window->SetIcon(DefaultIcon);
        }
        
        glfwSetWindowUserPointer(m_Window->GetNativeWindow(), this);
        // Set window callbacks
        glfwSetWindowCloseCallback(m_Window->GetNativeWindow(), [](GLFWwindow*)
        {
            GetCurrentApplication().RequireExit();
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
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            #if defined(HYDRO_PLATFORM_OPENGL)
            glViewport(0, 0, width, height);
            #endif
        });
        

        //TODO: Create an event system to handle window input
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


        m_AudioEngine = AudioEngine::Create();
        if(!m_AudioEngine->Init(44100))
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
