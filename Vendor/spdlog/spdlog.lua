
project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	staticruntime "On"
	flags "MultiProcessorCompile"
	
	location(build)
	targetdir(binaries)
	objdir(intermediate)

	files {
		"include/**.h",
		"src/**.cpp",
		"spdlog.lua"
	}
	
	defines { "SPDLOG_COMPILED_LIB" }

	includedirs "include"

	filter "Configurations:Debug*"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "Configurations:Release*"
		runtime "Release"
		optimize "On"
		symbols "Off"

