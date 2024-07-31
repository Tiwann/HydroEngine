
project "HydroEngine"
	kind "StaticLib"
	staticruntime "On"
	language "C++"
	cppdialect "C++20"
	flags "MultiProcessorCompile"

	targetdir(binaries)
	objdir(intermediate)
	
	postbuildcommands
	{
	    "{DELETE} " .. binaries .. "\\Shaders",
	    "{COPY} %{prj.location}Source\\Shaders " .. binaries .. "\\Shaders"
	}

	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Include/Hydro/Hydro.h",
		"Source/**.glsl",
		"HydroEngine.lua",
		"HydroEngine.natvis"
	}
	
	pchheader "HydroPCH.h"
	pchsource "Source/HydroPCH.cpp"

	includedirs
	{
	    "Source",
		"%{libs.glfw}/include",
		"%{libs.glad}/include",
		"%{libs.stb}/include",
		"%{libs.Vulkan}/Include",
		"%{libs.spdlog}/include",
		"%{libs.yaml}/include",
		"%{libs.ufbx}/include",
		"%{libs.box2d}/include",
		"%{libs.imgui}/include",
		"%{libs.imgui}/backends",
		"%{libs.Jolt}",
		"%{libs.miniaudio}/include",
	}

	links
	{
		"glfw",
		"stb",
		"spdlog",
		"yaml-cpp",
		"ufbx",
		"box2d",
		"imgui",
		"Jolt",
		"miniaudio"
	}

	defines 
	{  
	    "HYDRO_CORE",
	    "HYDRO_USE_DEFAULT_OPENGL_SHADER_COMPILER",
		"YAML_CPP_STATIC_DEFINE",
		"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
		
	}

	filter "Configurations:*Vulkan"
		links { "vulkan-1" }
		libdirs "%{libs.Vulkan}/Lib"
		defines { "HYDRO_PLATFORM_VULKAN", "GLFW_INCLUDE_VULKAN" }

	filter "Configurations:*DirectX"
		links { "d3d12", "dxgi", "d3dcompiler" }
		defines "HYDRO_PLATFORM_DIRECTX"
	
	filter "Configurations:*OpenGL"
	    links { "glad" }
	    defines "HYDRO_PLATFORM_OPENGL"
	

	filter "System:Windows"
		defines { "GLFW_EXPOSE_NATIVE_WIN32", "HYDRO_PLATFORM_WINDOWS", "_CRT_SECURE_NO_WARNINGS", "WIN32_LEAN_AND_MEAN" }
		
	filter "Configurations:*OpenGL or Configurations:*Vulkan"
	    removefiles { "Source/Platform/DirectX/**.h", "Source/Platform/DirectX/**.cpp" }
	    
	filter "Configurations:*OpenGL or Configurations:*DirectX"
    	removefiles { "Source/Platform/Vulkan/**.h", "Source/Platform/Vulkan/**.cpp" }

    filter "Configurations:*Vulkan or Configurations:*DirectX"
    	removefiles { "Source/Platform/OpenGL/**.h", "Source/Platform/OpenGL/**.cpp" }

	filter "System:Linux"
		defines { "HYDRO_PLATFORM_UNIX", "GLFW_EXPOSE_NATIVE_X11" }

	filter "Configurations:Debug*"
		runtime "Debug"
		optimize "Off"
		symbols "On"
		defines { "HYDRO_DEBUG" }
		

	filter "Configurations:Release*"
		runtime "Release"
		optimize "On"
		symbols "Off"
		defines { "HYDRO_RELEASE" }
		
