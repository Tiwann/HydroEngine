group "HydroFramework"
project "ufbx"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	flags "MultiProcessorCompile"
	
	targetdir(binaries)
	objdir(intermediate)

	files {
		"include/ufbx/ufbx.h",
        "src/ufbx.c",
		"ufbx.lua"
	}

	includedirs "include"

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
