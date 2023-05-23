group "HydroFramework"
group "shaderc"
project "libshaderc_util"
	kind "StaticLib"
	language "C++"
	flags "MultiProcessorCompile"

	targetdir(binaries)
	objdir(intermediate)


	files {
		"include/**.h",
		"src/**.cc",
		"libshaderc_util.lua"
	}

	includedirs {
		"include"
	}

	filter "Configurations:Debug"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "Configurations:Release"
		runtime "Release"
		optimize "On"
		symbols "Off"



