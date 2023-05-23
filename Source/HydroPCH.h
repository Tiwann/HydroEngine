#pragma once

///
/// Shared lib export macros
///
#if defined(_MSC_VER)
	#define HYDRO_EXPORT _declspec(dllexport)
	#define HYDRO_IMPORT _declspec(dllimport)
#elif defined(__GNUC__) && __GNUC__ >= 4
	#define HYDRO_EXPORT __attribute__(visibility("default"))
	#define HYDRO_IMPORT __attribute__(visibility("default"))
#else
	#define HYDRO_EXPORT
	#define HYDRO_IMPORT
#endif

#if !defined(HYDRO_API)
	#if defined(HYDRO_SHARED_LIB)
		#if defined(HYDRO_SHARED_EXPORT)
			#define HYDRO_API HYDRO_EXPORT
		#else
			#define HYDRO_API HYDRO_IMPORT
		#endif
	#else
		#define HYDRO_API
	#endif
#endif


#define HYDRO_VERSION_MAJ 1
#define HYDRO_VERSION_MIN 0
#define HYDRO_VERSION ((HYDRO_VERSION_MAJ << 8 & 0xFF00) | (HYDRO_VERSION_MIN & 0xFF))

#if !defined(HYDRO_RHI_NAME)
#if defined(HYDRO_PLATFORM_DIRECTX)
#define HYDRO_RHI_NAME "DirectX"
#elif defined(HYDRO_PLATFORM_VULKAN)
#define HYDRO_RHI_NAME "Vulkan"
#elif defined(HYDRO_PLATFORM_OPENGL)
#define HYDRO_RHI_NAME "OpenGL"
#endif
#endif

#if !defined(HYDRO_OS_NAME)
	#if defined(HYDRO_PLATFORM_WINDOWS)
		#define HYDRO_OS_NAME "Windows"
	#elif defined(HYDRO_PLATFORM_UNIX)
		#define HYDRO_OS_NAME "Linux"
	#endif
#endif
 

#if !defined(HYDRO_CONFIG_NAME)
#if defined(HYDRO_DEBUG)
#define HYDRO_CONFIG_NAME "Debug"
#else
#define HYDRO_CONFIG_NAME "Release"
#endif
#endif

#if defined(HYDRO_PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(HYDRO_PLATFORM_UNIX)
	#include <unistd.h>
#endif

#define HYDRO_NULL_MACRO (void)0

///
/// Include RHI headers
///
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <vulkan/vulkan.hpp>
#include <glad/gl.h>




///
/// Include std headers
///
///
///
#include <cstring>
#include <cassert>
#include <vector>
#include <array>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <exception>
#include <memory>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <string>


#include <glm/glm.hpp>
#include <glm/matrix.hpp>
using Handle = uint64_t;


