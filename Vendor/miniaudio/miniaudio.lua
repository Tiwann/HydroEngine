project "miniaudio"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	flags "MultiProcessorCompile"
	
	targetdir(binaries)
	objdir(intermediate)

	files {
		"include/miniaudio/miniaudio.h",
		"src/miniaudio.c",
		"miniaudio.lua"
	}

	includedirs "include"
	
	defines "MINIAUDIO_IMPLEMENTATION"

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
