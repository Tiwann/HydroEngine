group "HydroFramework"
project "stb"
	kind "StaticLib"
	staticruntime "On"
	language "C"

	targetdir(binaries)
	objdir(intermediate)

	files
	{
	    "stb.lua",
		"src/stb.c",
		"include/stb/stb_image.h",
		"include/stb/stb_image_resize.h",
		"include/stb/stb_image_write.h"
	}

	includedirs
	{
		"include"
	}
	
	
    filter "System:Windows"
        defines "_CRT_SECURE_NO_WARNINGS"

	filter "Configurations:Debug"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "Configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"



