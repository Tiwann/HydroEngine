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

namespace Hydro
{
    class Vector3;
}

namespace ImGui
{
    IMGUI_API void PushID(Hydro::GUID guid);
    IMGUI_API ImGuiID GetID(Hydro::GUID guid);
}

namespace ImGuizmo
{
    IMGUI_API void DecomposeMatrixToComponents(const float* matrix, Hydro::Vector3& translation, Hydro::Vector3& rotation, Hydro::Vector3& scale);
    IMGUI_API void RecomposeMatrixFromComponents(const Hydro::Vector3& translation, const Hydro::Vector3& rotation, const Hydro::Vector3& scale, float* matrix);
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
