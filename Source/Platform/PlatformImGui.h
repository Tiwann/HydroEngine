#pragma once
#include <imgui_impl_glfw.h>
#if defined(HYDRO_PLATFORM_OPENGL)
#include <imgui_impl_opengl3.h>
#elif defined(HYDRO_PLATFORM_VULKAN)
#include <imgui_impl_vulkan.h>
#elif defined(HYDRO_PLATFORM_DIRECTX)
#include <imgui_impl_dx12.h>
#endif

#include "Core/GUID.h"

namespace ImGui
{
    IMGUI_API void PushID(Hydro::GUID guid);
    IMGUI_API ImGuiID GetID(Hydro::GUID guid);
}

namespace Hydro
{
    class Application;

    namespace UI
    {
        bool Init(const Application* App);
        void SetHydroStyle();
        void BeginFrame();
        void EndFrame();
        void Shutdown();
        void Draw();
    }
}
