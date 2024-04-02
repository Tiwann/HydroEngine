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

#include "Input.h"

#if defined(HYDRO_PLATFORM_OPENGL)
#include <imgui_impl_opengl3.h>
#elif defined(HYDRO_PLATFORM_VULKAN)
#include <imgui_impl_vulkan.h>
#elif defined(HYDRO_PLATFORM_DIRECTX)
#include <imgui_impl_dx12.h>
#endif

namespace Hydro
{
    extern bool g_ApplicationRunning;

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
    }

    Application::~Application()
    {
        m_Window->Destroy();
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
        
        while(m_IsRunnning)
        {
            m_FrameStartTime = Time::GetTime();
            
            // Clear the back color
            m_Renderer->ClearDepthBuffer();
            m_Renderer->ClearColor(m_ClearColor);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            /*if(ImGui::Begin("Test Window"))
            {
                
                ImGui::End();
            }*/

            
            
            ImGui::EndFrame();
            
            
            OnUpdate(m_DeltaTime);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            glfwPollEvents();
            
            m_Renderer->SwapBuffers();
            m_FrameEndTime = Time::GetTime();
            m_DeltaTime = m_FrameEndTime - m_FrameStartTime;
        }


        OnExit();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        
        m_Window->Destroy();
        glfwTerminate();
    }

    void Application::OnInit()
    {
        m_Scene = CreateRef<Scene>();
        m_Scene->SetName("Default Scene");
        m_Scene->OnInit();
    }

    void Application::OnExit()
    {
        
    }

    static void UpdateWindowName(float Delta, Application* Application)
    {
        std::string NewWindowName = Application->GetWindow().GetName();
        if(Application->GetConfiguration().ShowDeltaTime)
        {
            NewWindowName.append(fmt::format(" | DeltaTime: {}", Delta));
        }

        if(Application->GetConfiguration().ShowFPS)
        {
            const uint32_t FPS = (uint32_t)(1.0f / Delta);
            NewWindowName.append(fmt::format(" FPS: {}", FPS));
        }
        Application->GetWindow().SetNameTemp(NewWindowName);
    }
    
    void Application::OnUpdate(float Delta)
    {     
        if(m_Configuration.ShowDeltaTime || m_Configuration.ShowFPS)
        {
            if(m_Configuration.WindowTitleUpdateTime != 0.0f)
            {
                static float Timer = 0.0f;
                Timer += Delta;
                if(Timer >= m_Configuration.WindowTitleUpdateTime)
                {
                    Timer = 0.0f;
                    UpdateWindowName(Delta, this);
                }
            }
            else
            {
                UpdateWindowName(Delta, this);
            }
        }
        m_Scene->OnUpdate(Delta);
    }

    const ApplicationConfiguration& Application::GetConfiguration() const
    {
        return m_Configuration;
    }

    const GraphicsSettings& Application::GetGraphicsSettings() const
    {
        return m_Configuration.Graphics;
    }
    

    Window& Application::GetWindow() const
    {
        return *m_Window;
    }

    void Application::RequireExit()
    {
        HYDRO_LOG(Application, Warning, "Exit required. Cleaning...");
        m_IsRunnning = false;
        g_ApplicationRunning = false;
    }

    void Application::RequireExitAndRestart()
    {
        HYDRO_LOG(Application, Warning, "Exit required. Cleaning... Application will restart");
        m_IsRunnning = false;
        g_ApplicationRunning = true;
    }
    
    Application& Application::GetCurrentApplication()
    {
        return *s_Instance;
    }

    void Application::SetClearColor(const Color& color)
    {
        m_ClearColor = color;
    }

    void Application::SetCursorVisible(bool Visible) const
    {
        Cursor::SetCursorVisible(m_Window, Visible);
    }

    RendererBackend& Application::GetRenderer() const
    {
        return *m_Renderer;
    }

    Scene& Application::GetScene() const
    {
        return *m_Scene;
    }
    
    bool Application::PreInitialize()
    {
        // Init spdlog logger
        Log::Init();
        
        // Init GLFW
        if(!glfwInit())
        {
            HYDRO_LOG(Application, Error, "Failed to initilaize glfw!");
            return false;
        }
        
        HYDRO_LOG(Application, Info, "Using GLFW version {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

        glfwSetErrorCallback([](int code, const char* message)
        {
            HYDRO_LOG(Application, Warning, "[GLFW] Error {}: {}", code, message);
        });
        
        // Create Window, set its close callback
        HYDRO_LOG(Application, Trace, "Creating window...");
        m_Configuration = CreateConfiguration();
        if(m_Configuration.ShowGraphicsAPIName) m_Configuration.AppName = fmt::format("{} | {}", m_Configuration.AppName, HYDRO_RHI_NAME);
        if(m_Configuration.ShowOSName) m_Configuration.AppName = fmt::format("{} {}", m_Configuration.AppName, HYDRO_OS_NAME);
        if(m_Configuration.ShowConfiguration) m_Configuration.AppName = fmt::format("{}", m_Configuration.AppName, HYDRO_CONFIG_NAME);
        m_Window = Window::Create(m_Configuration.AppName, m_Configuration.WindowWidth, m_Configuration.WindowHeight, m_Configuration.WindowResizable);

        
        glfwSetWindowUserPointer(m_Window->GetNativeWindow(), this);
        // Set window callbacks
        m_Window->SetCloseCallback([](GLFWwindow* window)
        {
            GetCurrentApplication().RequireExit();
        });

        m_Window->SetFocusCallback([](GLFWwindow* window, int focus){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_HasFocus = (bool)focus;
            const std::string message = focus ? "Window focused" : "Window unfocused";
            HYDRO_LOG(Application, Trace, "[WINDOW] {}", message);
        });

        m_Window->SetMaximizeCallback([](GLFWwindow* window, int maximized){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Maximized = (bool)maximized;
            if(maximized) HYDRO_LOG(Application, Trace, "[WINDOW] maximized");
        });

        m_Window->SetPositionCallback([](GLFWwindow* window, int x, int y){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_PositionX = x;
            application->m_Window->m_PositionY = y;
        });

        m_Window->SetResizeCallback([](GLFWwindow* window, int width, int height){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Width = width;
            application->m_Window->m_Height = height;
            #if defined(HYDRO_PLATFORM_OPENGL)
            glViewport(0, 0, width, height);
            #endif
        });

        m_Window->SetIconifyCallback([](GLFWwindow* window, int iconified)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Minimized = (bool)iconified;
            if(iconified) HYDRO_LOG(Application, Trace, "[WINDOW] minimized");
        });

        m_Window->SetFramebufferCallback([](GLFWwindow* window, int width, int height)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            #if defined(HYDRO_PLATFORM_OPENGL)
            glViewport(0, 0, width, height);
            #endif
        });

        m_Window->SetRefreshCallback([](GLFWwindow* window)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->OnUpdate(0.0f);
            glfwSwapBuffers(window);
            #if defined(HYDRO_PLATFORM_OPENGL)
            glFinish();
            #endif
        });



        //TODO: Create an event system to handle window input
        m_Window->SetKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mod)
        {
            /*switch (action)
            {
            case GLFW_PRESS:
                if(Input::States[key].WasPressed)
                {
                    Input::States[key].IsPressed = false;
                    Input::States[key].IsHold = true;
                } else
                {
                    Input::States[key].IsPressed = true;
                    Input::States[key].WasPressed = true;
                    Input::States[key].IsHold = false;
                }
                break;
            case GLFW_RELEASE:
                Input::States[key].IsRelease = true;
                Input::States[key].IsPressed = false;
                Input::States[key].IsHold = false;
                Input::States[key].WasPressed = false;
                break;
            default: break;
            }

            if(key == SPACE && Input::States[SPACE].IsPressed)
            {
                HYDRO_LOG(Application, Error, "Space Key pressed!");
            }*/
        });
        
        
        HYDRO_LOG(Application, Info, "Window successfully created!");

        HYDRO_LOG(Application, Trace, "Loading window icon(s)...");
        const Ref<Image> WindowIcon = GetWindowIcon();
        m_Window->SetIcon(WindowIcon);
        HYDRO_LOG(Application, Info, "Successfully loaded window icon(s)");

        
        if(!m_Window->IsValid())
        {
            HYDRO_LOG(Application, Error, "Failed to create window!");
            return false;
        }

        HYDRO_LOG(Application, Trace, "Creating Renderer...");
        
        m_Renderer = RendererBackend::Create();
        if(!m_Renderer->IsReady())
        {
            HYDRO_LOG(Application, Error, "Failed to create renderer!");
            return false;
        }

        HYDRO_LOG(Application, Info, "Renderer created!");

        IMGUI_CHECKVERSION();
        ImGuiContext* ImGuiContext = ImGui::CreateContext();
        ImGui::SetCurrentContext(ImGuiContext);
#if defined(HYDRO_PLATFORM_OPENGL)
        if(!ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for GLFW!");
            return false;
        }

        if(!ImGui_ImplOpenGL3_Init("#version 460 core"))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for OpenGL!");
            return false;
        }
#elif defined(HYDRO_PLATFORM_VULKAN)
        if(!ImGui_ImplGlfw_InitForVulkan(m_Window->GetNativeWindow(), true))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for GLFW!");
            return false;
        }

        //TODO: Fill this struct
        ImGui_ImplVulkan_InitInfo ImGuiVulkanInitInfo{};
        
        if(!ImGui_ImplVulkan_Init(&ImGuiVulkanInitInfo))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for Vulkan!");
            return false;
        }
#elif defined(HYDRO_PLATFORM_DIRECTX)
        if(!ImGui_ImplGlfw_InitForOther(m_Window->GetNativeWindow(), true))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for GLFW!");
            return false;
        }

        if(!ImGui_ImplDX12_Init(&ImGuiVulkanInitInfo))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for Vulkan!");
            return false;
        }
#endif
        return true;
    }
}
