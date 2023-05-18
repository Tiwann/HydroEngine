#include "HydroPCH.h"
#include "Application.h"
#include "StringFormat.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Image.h"

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
            std::cerr << "Failed to init core!\n";
            return;
        }
        
        OnInit();
        
        while(m_IsRunnning)
        {
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
        const auto UpdateWindowName = [&delta, this]()
        {
            String NewWindowName = *m_Window->GetName();
            if(m_Specifications.ShowDeltaTime)
            {
                NewWindowName.Append(Format(" | DeltaTime: %f", delta));
            }

            if(m_Specifications.ShowFPS)
            {
                const uint32_t FPS = (uint32_t)((float)1 / delta);
                NewWindowName.Append(Format(" FPS: %d", FPS));
            }
            m_Window->SetNameTemp(NewWindowName);
        };
        
        if(m_Specifications.ShowDeltaTime || m_Specifications.ShowFPS)
        {
            if(m_Specifications.WindowTitleUpdateTime != 0.0f)
            {
                static float Timer = 0.0f;
                Timer += delta;
                if(Timer >= m_Specifications.WindowTitleUpdateTime)
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

    const ApplicationSpecs& Application::GetSpecifications() const
    {
        return m_Specifications;
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
        std::cout << "Exit Required. Cleaning...\n";
        m_IsRunnning = false;
        g_ApplicationRunning = Restart;
    }

    Application& Application::GetCurrentApplication()
    {
        return *instance;
    }

    bool Application::InitCore()
    {
        // Init GLFW
        if(!glfwInit())
        {
            std::cerr << "Failed to init glfw!\n";
            return false;
        }

        // Create Window, set its close callback
        m_Specifications = CreateSpecifications();
        if(m_Specifications.ShowGraphicsAPIName) m_Specifications.AppName = Format("%s | %s", *m_Specifications.AppName, HYDRO_RHI_NAME);
        if(m_Specifications.ShowOSName) m_Specifications.AppName = Format("%s %s", *m_Specifications.AppName, HYDRO_OS_NAME);
        if(m_Specifications.ShowConfiguration) m_Specifications.AppName = Format("%s %s", *m_Specifications.AppName, HYDRO_CONFIG_NAME);
        m_Window = Window::Create(m_Specifications.AppName, m_Specifications.WindowWidth, m_Specifications.WindowHeight, m_Specifications.WindowResizable);
        glfwSetWindowUserPointer(m_Window->GetNativeWindow(), this);

        // Set window claabacks
        m_Window->SetCloseCallback(Function<void, GLFWwindow*>([](GLFWwindow* window)
        {
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_IsRunnning = false;
            g_ApplicationRunning = false;
        }));

        m_Window->SetFocusCallback(Function<void, GLFWwindow*, int>([](GLFWwindow* window, int focus){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_HasFocus = (bool)focus;
        }));

        m_Window->SetMaximizeCallback(Function<void, GLFWwindow*, int>([](GLFWwindow* window, int maximized){
            Application* application = (Application*)glfwGetWindowUserPointer(window);
            application->m_Window->m_Maximized = (bool)maximized;
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

        

        
        const std::vector<Ref<Image>> Icons = LoadWindowIcons();
        m_Window->SetIcons(Icons);

        
        
        if(!m_Window->IsValid())
        {
            std::cerr << "Failed to create window!\n";
            return false;
        }

        m_Renderer = CreateRef<Renderer>(GraphicsDevice::Create());
        return true;
    }
    
}


