project "glfw"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	flags "MultiProcessorCompile"
	
	location(build)
    targetdir (binaries)
    objdir (intermediate)
	
	files {
		"glfw.lua",
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",
		"src/internal.h",
		"src/platform.h",
		"src/mappings.h",
		"src/mappings.h.in",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/platform.c",
		"src/platform.h",
		"src/vulkan.c",
		"src/window.c",
		"src/egl_context.c",
		"src/osmesa_context.c",
		"src/null_platform.h",
		"src/null_joystick.h",
		"src/null_init.c",
		
		"src/null_monitor.c",
		"src/null_window.c",
		"src/null_joystick.c",
	}

	includedirs "include"
	defines "_GLFW_USE_OPTIMUS_HPG"

	filter "configurations:Debug*"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release*"
		runtime "Release"
		optimize "On"
		symbols "Off"

	filter "system:windows"
		systemversion "latest"

		files {
			"src/win32_init.c",
			"src/win32_module.c",
			"src/win32_joystick.c",
			"src/win32_joystick.h",
			"src/win32_platform.h",
			"src/win32_monitor.c",
			"src/win32_time.h",
			"src/win32_time.c",
			"src/win32_thread.h",
			"src/win32_thread.c",
			"src/win32_window.c",
			"src/wgl_context.c",
		}

		defines {
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
	
	filter "system:linux"
		pic "On"
		systemversion "latest"

		files {
			"src/x11_init.c",
			"src/x11_platform.h",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_time.c",
			"src/posix_time.h",
			"src/posix_thread.c",
			"src/posix_thread.h",
			"src/posix_module.c",
			"src/posix_poll.c",
			"src/posix_poll.h",
			"src/glx_context.c",
			"src/osmesa_context.c",
			"src/linux_joystick.c",
			"src/linux_joystick.h",
		}

		defines {
			"_GLFW_X11"
		}