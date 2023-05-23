group "HydroFramework"
group "shaderc"
project "libshaderc"
	kind "StaticLib"
	language "C++"
	flags "MultiProcessorCompile"

	targetdir(binaries)
	objdir(intermediate)


	files {
		"include/shaderc/env.h",
		"include/shaderc/shaderc.h",
		"include/shaderc/shaderc.hpp",
		"include/shaderc/status.h",
		"include/shaderc/visibility.h",
		"src/shaderc.cc",
		"src/shaderc_private.h",
		"libshaderc.lua"
	}

	includedirs {
		"include",
        "%{libs.libshaderc_util}/include"
	}

    links "libshaderc_util"

	filter "Configurations:Debug"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "Configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"



