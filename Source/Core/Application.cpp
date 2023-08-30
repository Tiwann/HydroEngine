#include "HydroPCH.h"
#include "Application.h"
#include <GLFW/glfw3.h>


#include "Image.h"
#include "Input.h"
#include "Log.h"
#include "Time.h"
#include "Color.h"
#include "Platform/RendererDevice.h"

#include <spdlog/fmt/fmt.h>
#include <GLFW/glfw3native.h>

#include "LogVerbosity.h"

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
        HYDRO_LOG(Application, Verbosity::Trace, "This is a test log");
        if(!InitCore())
        {
            HYDRO_LOG(Application, Verbosity::Error, "Failed to init Hydro Framework Core!");
            return;
        }
        
        OnInit();
        HYDRO_ASSERT(m_OnInit, "An error occured. Did you call Super::OnInit ?");
        
        while(m_IsRunnning)
        {
            Time::m_Time = (float)glfwGetTime();
            m_FrameStartTime = (float)glfwGetTime();
            Input::Reset();

            // Clear the back color
            m_Renderer->Clear();
            m_Renderer->Clear(m_ClearColor);
            
            OnUpdate(m_DeltaTime);
            glfwPollEvents();
            m_Renderer->SwapBuffers();
            m_FrameEndTime = (float)glfwGetTime();
            m_DeltaTime = m_FrameEndTime - m_FrameStartTime;
        }


        OnExit();
        m_Window->Destroy();
        glfwTerminate();
    }

    void Application::OnInit()
    {
        m_OnInit = true;
        m_Window->Show();
    }

    void Application::OnExit()
    {
        
    }

    void Application::OnUpdate(float delta)
    {
        const auto UpdateWindowName = [&delta, this]
        {
            std::string NewWindowName = m_Window->GetName();
            if(m_Configuration.ShowDeltaTime)
            {
                NewWindowName.append(fmt::format(" | DeltaTime: {}", delta));
            }

            if(m_Configuration.ShowFPS)
            {
                const uint32_t FPS = (uint32_t)((float)1 / delta);
                NewWindowName.append(fmt::format(" FPS: {}", FPS));
            }
            m_Window->SetNameTemp(NewWindowName);
        };
        
        if(m_Configuration.ShowDeltaTime || m_Configuration.ShowFPS)
        {
            if(m_Configuration.WindowTitleUpdateTime != 0.0f)
            {
                static float Timer = 0.0f;
                Timer += delta;
                if(Timer >= m_Configuration.WindowTitleUpdateTime)
                {
                    Timer = 0.0f;
                    UpdateWindowName();
                }
            }
            else
            {
                UpdateWindowName();
            }
        }
    }

    const ApplicationConfiguration& Application::GetConfiguration() const
    {
        return m_Configuration;
    }

    const GraphicsSettings& Application::GetGraphicsSettings() const
    {
        return m_Configuration.GraphicsSettings;
    }

    const Window& Application::GetWindow() const
    {
        return *m_Window;
    }

    Window& Application::GetWindow()
    {
        return *m_Window;
    }
    

    void Application::RequireExit(bool Restart)
    {
        HYDRO_LOG(Application, Warning, "Exit required. Cleaning...");
        if(Restart)
        {
            HYDRO_LOG(Application, Warning, "Application will restart.");
        }
        m_IsRunnning = false;
        g_ApplicationRunning = Restart;
    }

    Application& Application::GetCurrentApplication()
    {
        return *s_Instance;
    }

    void Application::SetClearColor(const Color& color)
    {
        m_ClearColor = color;
    }

    Renderer& Application::GetRenderer() const
    {
        return *m_Renderer;
    }

    bool Application::InitCore()
    {
        // Init spdlog logger
        Log::Init();
        Time::m_Time = (float)glfwGetTime();
        
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
        HYDRO_LOG(Application, Trace, "Creating window...\n");
        m_Configuration = CreateConfiguration();
        if(m_Configuration.ShowGraphicsAPIName) m_Configuration.AppName = fmt::format("{} | {}", m_Configuration.AppName, HYDRO_RHI_NAME);
        if(m_Configuration.ShowOSName) m_Configuration.AppName = fmt::format("{} {}", m_Configuration.AppName, HYDRO_OS_NAME);
        if(m_Configuration.ShowConfiguration) m_Configuration.AppName = fmt::format("{}", m_Configuration.AppName, HYDRO_CONFIG_NAME);
        m_Window = Window::Create(m_Configuration.AppName, m_Configuration.WindowWidth, m_Configuration.WindowHeight, m_Configuration.WindowResizable);
        
        glfwSetWindowUserPointer(m_Window->GetNativeWindow(), this);
        // Set window callbacks
        m_Window->SetCloseCallback(Function<void, GLFWwindow*>([](GLFWwindow* window)
        {
            GetCurrentApplication().RequireExit(false);
        }));

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



        //TODO: Create an event system to handle window input
        m_Window->SetKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mod)
        {
            HYDRO_LOG(Application, Trace, "KeyCallback:  Key: {} Scancode: {} Action: {} Mod: {}", key, scancode, action, mod);
            if(action == GLFW_PRESS)
            {
                Input::m_KeyStates[key].Pressed = true;
            } else if(action == GLFW_RELEASE)
            {
                Input::m_KeyStates[key].Up = true;
            }
        });
        
        
        HYDRO_LOG(Application, Info, "Window successfully created!");

        HYDRO_LOG(Application, Trace, "Loading window icon(s)...");
        const std::vector<Ref<Image>> Icons = LoadWindowIcons();
        m_Window->SetIcons(Icons);
        HYDRO_LOG(Application, Info, "Successfully loaded window icon(s)");

        
        if(!m_Window->IsValid())
        {
            HYDRO_LOG(Application, Error, "Failed to create window!");
            return false;
        }

        HYDRO_LOG(Application, Trace, "Creating Renderer...");
        m_Renderer = CreateRef<Renderer>(RendererDevice::Create());
        if(!m_Renderer->IsReady())
        {
            HYDRO_LOG(Application, Error, "Failed to create renderer!");
            return false;
        }
        HYDRO_LOG(Application, Info, "Renderer created!");
        return true;
    }
}
