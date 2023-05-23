#include "HydroPCH.h"
#include "Application.h"
#include "StringFormat.h"
#include <GLFW/glfw3.h>


#include "Image.h"
#include "Input.h"
#include "Log.h"
#include "Time.h"

namespace Hydro
{
    extern bool g_ApplicationRunning;

    Application* Application::instance = nullptr;

    Application::Application()
    {
        instance = this;
    }

    Application::~Application()
    {
        m_Window->Destroy();
    }

    void Application::Run()
    {
        if(!InitCore())
        {
            HYDRO_LOG_ERROR("Failed to init Hydro Framework Core!");
            return;
        }
        
        OnInit();
        
        while(m_IsRunnning)
        {
            Time::m_Time = (float)glfwGetTime();
            m_FrameStartTime = (float)glfwGetTime();

            // Clear the back color
            m_Renderer->Clear();
            m_Renderer->Clear(Color::Black);
            
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
        
    }

    void Application::OnExit()
    {
        
    }

    void Application::OnUpdate(float delta)
    {
        const auto UpdateWindowName = [&delta, this]
        {
            String NewWindowName = m_Window->GetName();
            if(m_Configuration.ShowDeltaTime)
            {
                NewWindowName.Append(Format(" | DeltaTime: %f", delta));
            }

            if(m_Configuration.ShowFPS)
            {
                const uint32_t FPS = (uint32_t)((float)1 / delta);
                NewWindowName.Append(Format(" FPS: %d", FPS));
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
        HYDRO_LOG_WARNING("Exit required. Cleaning...");
        if(Restart) HYDRO_LOG_WARNING("Application will restart.");
        m_IsRunnning = false;
        g_ApplicationRunning = Restart;
    }

    Application& Application::GetCurrentApplication()
    {
        return *instance;
    }

    bool Application::InitCore()
    {
        // Init spdlog logger
        Log::Init();
        Time::m_Time = (float)glfwGetTime();
        
        // Init GLFW
        if(!glfwInit())
        {
            HYDRO_LOG_ERROR("Failed to initilaize glfw!");
            return false;
        }
        HYDRO_LOG_INFO("Using GLFW version {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

        glfwSetErrorCallback([](int code, const char* message)
        {
            HYDRO_LOG_WARNING("[GLFW] Error {}: {}", code, message);
        });
        
        // Create Window, set its close callback
        HYDRO_LOG_TRACE("Creating window...\n");
        m_Configuration = CreateConfiguration();
        if(m_Configuration.ShowGraphicsAPIName) m_Configuration.AppName = Format("%s | %s", *m_Configuration.AppName, HYDRO_RHI_NAME);
        if(m_Configuration.ShowOSName) m_Configuration.AppName = Format("%s %s", *m_Configuration.AppName, HYDRO_OS_NAME);
        if(m_Configuration.ShowConfiguration) m_Configuration.AppName = Format("%s %s", *m_Configuration.AppName, HYDRO_CONFIG_NAME);
        m_Window = Window::Create(m_Configuration.AppName, m_Configuration.WindowWidth, m_Configuration.WindowHeight, m_Configuration.WindowResizable);
        glfwSetWindowUserPointer(m_Window->GetNativeWindow(), this);
        // Set window callbacks
        m_Window->SetCloseCallback(Function<void, GLFWwindow*>([](GLFWwindow* window)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            GetCurrentApplication().RequireExit(false);
        }));

        m_Window->SetFocusCallback(Function<void, GLFWwindow*, int>([](GLFWwindow* window, int focus){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_HasFocus = (bool)focus;
            const String message = focus ? "Window focused" : "Window unfocused";
            HYDRO_LOG_TRACE("[WINDOW] {}", *message);
        }));

        m_Window->SetMaximizeCallback(Function<void, GLFWwindow*, int>([](GLFWwindow* window, int maximized){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Maximized = (bool)maximized;
            if(maximized) HYDRO_LOG_TRACE("[WINDOW] maximized");
        }));

        m_Window->SetPositionCallback(Function<void, GLFWwindow*, int, int>([](GLFWwindow* window, int x, int y){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_PositionX = x;
            application->m_Window->m_PositionY = y;
        }));

        m_Window->SetResizeCallback(Function<void, GLFWwindow*, int, int>([](GLFWwindow* window, int width, int height){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Width = width;
            application->m_Window->m_Height = height;
            #if defined(HYDRO_PLATFORM_OPENGL)
            glViewport(0, 0, width, height);
            #endif
        }));

        m_Window->SetIconifyCallback(Function<void, GLFWwindow*, int>([](GLFWwindow* window, int iconified)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Minimized = (bool)iconified;
            if(iconified) HYDRO_LOG_TRACE("[WINDOW] minimized");
        }));



        //TODO: Create an event system to handle window input
        m_Window->SetKeyCallback(Function<void, GLFWwindow*, int, int, int, int>([](GLFWwindow* window, int key, int scancode, int action, int mod)
        {
            //HYDRO_LOG_TRACE("KeyCallback:\n\tKey: {}\n\tScancode: {}\n\tAction: {}\n\tMod: {}", key, scancode, action, mod);
            if(action == GLFW_PRESS)
            {
                Input::m_Keys[key] = true;
            } else if(action == GLFW_RELEASE)
            {
                Input::m_Keys[key] = false;
            }
            //HYDRO_LOG_TRACE("KeyCallback: {}", Input::m_Keys[scancode]);
        }));
        
        
        HYDRO_LOG_INFO("Window successfully created!");

        HYDRO_LOG_TRACE("Loading window icon(s)...");
        const std::vector<Ref<Image>> Icons = LoadWindowIcons();
        m_Window->SetIcons(Icons);
        HYDRO_LOG_INFO("Successfully loaded window icon(s)");

        
        if(!m_Window->IsValid())
        {
            HYDRO_LOG_ERROR("Failed to create window!");
            return false;
        }

        HYDRO_LOG_TRACE("Creating Renderer...");
        m_Renderer = CreateRef<Renderer>(RendererDevice::Create());
        if(!m_Renderer->IsReady())
        {
            HYDRO_LOG_ERROR("Failed to create renderer!");
            return false;
        }
        HYDRO_LOG_INFO("Renderer created!");
        return true;
    }
}


