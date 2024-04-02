project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"
    staticruntime "On"
    flags "MultiProcessorCompile"
	
	targetdir(binaries)
	objdir(intermediate)

    files
    {
        "include/**.h",
        "src/**.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_glfw.cpp",
        "imgui.lua"
    }

    includedirs 
    {
        "include",
        "%{libs.glfw}/include"
    }

    filter "Configurations:*OpenGL"
        files 
        {
            "backends/imgui_impl_opengl3.h",
            "backends/imgui_impl_opengl3.cpp",
        }

    filter "Configurations:*Vulkan"
        files 
        {
            "backends/imgui_impl_vulkan.h",
            "backends/imgui_impl_vulkan.cpp",
        }

    filter "Configurations:*DirectX"
        files 
        {
            "backends/imgui_impl_dx12.h",
            "backends/imgui_impl_dx12.cpp",
        }

    filter "Configurations:Debug*"
	    runtime "Debug"
	    optimize "Off"
	    symbols "On"

	filter "Configurations:Release*"
		runtime "Release"
		optimize "On"
		symbols "Off"
	
	filter "System:Linux"
		pic "On"