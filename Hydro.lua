group "HydroFramework"
project "Hydro"
	kind "StaticLib"
	staticruntime "On"
	language "C++"
	cppdialect "C++20"
	flags "MultiProcessorCompile"

	targetdir(binaries)
	objdir(intermediate)

	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Include/**.h",
		"Source/**.glsl",
		"Source/**.vert",
		"Source/**.frag",
		"External/spdlog/**.h",
		"External/spdlog/**.cpp",
		"Hydro.lua"
	}
	
	pchheader "HydroPCH.h"
	pchsource "Source/HydroPCH.cpp"

	includedirs
	{
	    "Source",
		"%{libs.glfw}/include",
		"%{libs.stb}/include",
		"%{libs.Vulkan}/Include",
		"%{libs.glad}/include",
		"%{libs.spdlog}/include",
		"%{libs.libshaderc}/include",
	}

	libdirs {
		"%{libs.libshaderc}/lib",
	}
	
	links
	{
		"glfw",
		"stb",
	}

	defines { "SPDLOG_COMPILED_LIB", "HYDRO_CORE", "HYDRO_SHADER_CACHE_DIRECTORY=\"Assets/ShaderCache/\"" }

	filter "Platforms:Vulkan"
		links { "vulkan-1" }
		libdirs "%{libs.Vulkan}/Lib"
		defines { "HYDRO_PLATFORM_VULKAN", "GLFW_INCLUDE_VULKAN" }

	filter "Platforms:DirectX"
		links { "d3d12", "dxgi", "d3dcompiler" }
		defines "HYDRO_PLATFORM_DIRECTX"
	
	filter "Platforms:OpenGL"
	    links { "glad", "opengl32" }
	    defines "HYDRO_PLATFORM_OPENGL"
	

	filter "System:Windows"
		defines { "GLFW_EXPOSE_NATIVE_WIN32", "HYDRO_PLATFORM_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
		toolset "msc"

	filter "System:Linux"
		toolset "gcc"
		defines { "HYDRO_PLATFORM_UNIX" }
		removefiles { "**/DirectXDevice*" }
		

	filter "Configurations:Debug"
		runtime "Debug"
		optimize "Off"
		symbols "On"
		defines "HYDRO_DEBUG"
		links {
			"shaderc_combinedd"
		}

	filter "Configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"
		defines "HYDRO_RELEASE"
		links {
			"shaderc_combined"
		}
