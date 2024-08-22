#include "HydroPCH.h"
#include "PlatformImGui.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/LogCategory.h"
#include "Core/Log.h"
#include "Core/LogVerbosity.h"
#include "Editor/Font.h"
#include "imgui/imgui_internal.h"
#include "ImGuizmo/ImGuizmo.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(ImGui, "IMGUI");
#define HYDRO_IMGUI_ERROR(str, ...) HYDRO_LOG(ImGui, Verbosity::Error, str, __VA_ARGS__)

#define HYDRO_EDITOR_FONT_SIZE 16.0f


namespace Hydro::UI
{
    bool Init(const Application* App)
    {
        if(!IMGUI_CHECKVERSION())
        {
            HYDRO_IMGUI_ERROR("ImGui version check failed!");
            return false;
        }

       
        ImGuiContext* ImGuiContext = ImGui::CreateContext();
        
        ImGuiIO& IO = ImGui::GetIO();
        IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        
        for(size_t i = 0; i < NumFonts; i++)
        {
            Fonts[i] = IO.Fonts->AddFontFromFileTTF(FontsPaths[i], HYDRO_EDITOR_FONT_SIZE);
        }
        IO.FontDefault = Fonts[JetBrainsMono_SemiBold];
        
        if(!ImGuiContext)
        {
            HYDRO_IMGUI_ERROR("Failed to create ImGui context!");
            return false;
        }
        ImGui::SetCurrentContext(ImGuiContext);
        ImGuizmo::SetImGuiContext(ImGuiContext);
        SetHydroStyle();
 

        const Ref<Window>& Window = App->GetWindow();
        GLFWwindow* NativeWindow = Window->GetNativeWindow();
#if defined(HYDRO_PLATFORM_OPENGL)
        if(!ImGui_ImplGlfw_InitForOpenGL(NativeWindow, true))
        {
            HYDRO_IMGUI_ERROR("Failed to initialize ImGui for GLFW!");
            return false;
        }

        if(!ImGui_ImplOpenGL3_Init("#version 460 core"))
        {
            HYDRO_IMGUI_ERROR("Failed to initialize ImGui for OpenGL!");
            return false;
        }
#elif defined(HYDRO_PLATFORM_VULKAN)
        
        if(!ImGui_ImplGlfw_InitForVulkan(NativeWindow, true))
        {
            HYDRO_IMGUI_ERROR("Failed to initialize ImGui for GLFW!");
            return false;
        }

        const Ref<VulkanRendererBackend>& RendererBackend = Cast<VulkanRendererBackend>(App->GetRendererBackend());
        ImGui_ImplVulkan_InitInfo InitInfo{};
        InitInfo.Instance = RendererBackend->GetInstance();
        InitInfo.Device = RendererBackend->GetDevice();
        InitInfo.PhysicalDevice = RendererBackend->GetPhysicalDevice();
        InitInfo.Queue = RendererBackend->GetGraphicsQueue();
        InitInfo.ImageCount = RendererBackend->GetImageCount();
        
        InitInfo.CheckVkResultFn = [](VkResult Result)
        {
            if(Result != VK_SUCCESS)
            {
                HYDRO_IMGUI_ERROR("Something went wrong.");
                Application::GetCurrentApplication().RequireExit();
            }
        };
        
        
        
        if(!ImGui_ImplVulkan_Init(&InitInfo))
        {
            HYDRO_LOG(Application, Info, "Failed to initialize ImGui for Vulkan!");
            return false;
        }

#elif defined(HYDRO_PLATFORM_DIRECTX)
        if(!ImGui_ImplGlfw_InitForOther(NativeWindow, true))
        {
            HYDRO_IMGUI_ERROR("Failed to initialize ImGui for GLFW(DX12)!");
            return false;
        }
        
        const Ref<DirectXRendererBackend> RendererBackend = Cast<DirectXRendererBackend>(App->GetRendererBackend());
        const ID3D12Device* Device = RendererBackend->GetDevice();
        
        if(!ImGui_ImplDX12_Init(Device, ))
        {
            HYDRO_IMGUI_ERROR("Failed to initailize ImGui for DirectX12!");
            return false;
        }
#endif
        return true;
    }

    void SetHydroStyle()
    {
        ImGuiStyle& Style = ImGui::GetStyle();
        ImVec4* Colors = Style.Colors;
        Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        Colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        Colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        Colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        Colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        Colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        Colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        Colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        Colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        Colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        Colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        Colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        Colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        Colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        Colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        Colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        Colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        Colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        Colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        Colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        Colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
        
        Style.WindowPadding = ImVec2(8.00f, 8.00f);
        Style.FramePadding = ImVec2(5.00f, 2.00f);
        Style.CellPadding = ImVec2(6.00f, 6.00f);
        Style.ItemSpacing = ImVec2(6.00f, 6.00f);
        Style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
        Style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
        Style.IndentSpacing = 25;
        Style.ScrollbarSize = 15;
        Style.GrabMinSize = 10;
        Style.WindowBorderSize = 1;
        Style.ChildBorderSize = 1;
        Style.PopupBorderSize = 1;
        Style.FrameBorderSize = 1;
        Style.TabBorderSize = 1;
        Style.WindowRounding = 7;
        Style.ChildRounding = 4;
        Style.FrameRounding = 3;
        Style.PopupRounding = 4;
        Style.ScrollbarRounding = 9;
        Style.GrabRounding = 3;
        Style.LogSliderDeadzone = 4;
        Style.TabRounding = 4;
    }


    void BeginFrame()
    {
#if defined(HYDRO_PLATFORM_OPENGL)
        ImGui_ImplOpenGL3_NewFrame();
#elif defined(HYDRO_PLATFORM_VULKAN)
        ImGui_ImplVulkan_NewFrame();
#elif defined(HYDRO_PLATFORM_DIRECTX)
        ImGui_ImplDX12_NewFrame();
#endif
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
    }

    void EndFrame()
    {
        ImGui::EndFrame();
    }

    void Shutdown()
    {
#if defined(HYDRO_PLATFORM_OPENGL)
        ImGui_ImplOpenGL3_Shutdown();
#elif defined(HYDRO_PLATFORM_VULKAN)
        ImGui_ImplVulkan_Shutdown();
#elif defined(HYDRO_PLATFORM_DIRECTX)
        ImGui_ImplDX12_Shutdown();
#endif
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Draw()
    {
        ImGui::Render();
        ImDrawData* Data = ImGui::GetDrawData();
#if defined(HYDRO_PLATFORM_OPENGL)
        ImGui_ImplOpenGL3_RenderDrawData(Data);
        
#elif defined(HYDRO_PLATFORM_VULKAN)
        (void)Data;
        //ImGui_ImplVulkan_RenderDrawData(Data);
#elif defined(HYDRO_PLATFORM_DIRECTX)
        ImGui_ImplDX12_RenderDrawData();
#endif
    }
}

namespace ImGui
{
    void PushID(const Hydro::GUID& guid)
    {
        const uint64_t* begin = guid.GetValues();
        const uint64_t* end = begin + 2;
        PushID((const char*)begin, (const char*)end);
    }

    ImGuiID GetID(const Hydro::GUID& guid)
    {
        ImGuiWindow* window = GImGui->CurrentWindow;
        const uint64_t* begin = guid.GetValues();
        const uint64_t* end = begin + 2;
        return window->GetID((const char*)begin, (const char*)end);
    }  
}

void ImGuizmo::DecomposeMatrixToComponents(const float* matrix, Hydro::Vector3& translation, Hydro::Vector3& rotation, Hydro::Vector3& scale)
{
    ImGuizmo::DecomposeMatrixToComponents(matrix, translation.ValuePtr(), rotation.ValuePtr(), scale.ValuePtr());
}

void ImGuizmo::RecomposeMatrixFromComponents(const Hydro::Vector3& translation, const Hydro::Vector3& rotation,
    const Hydro::Vector3& scale, float* matrix)
{
    ImGuizmo::RecomposeMatrixFromComponents(translation.ValuePtr(), rotation.ValuePtr(), scale.ValuePtr(), matrix);
}
