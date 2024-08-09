
project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	flags "MultiProcessorCompile"

    location(build)
	targetdir(binaries)
	objdir(intermediate)

	files {
		"src/**.h",
		"src/**.cpp",
		"include/**.h",
		"yaml-cpp.lua"
	}

	includedirs "include"

	defines  "YAML_CPP_STATIC_DEFINE"

	filter "Configurations:Debug*"
		runtime "Debug"
		optimize "Off"
		symbols "On"

	filter "Configurations:Release*"
		runtime "Release"
		optimize "On"
		symbols "Off"