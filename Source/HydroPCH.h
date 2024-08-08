#pragma once
#if defined(HYDRO_PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(HYDRO_PLATFORM_UNIX)
	#include <unistd.h>
#endif


#if defined(HYDRO_PLATFORM_DIRECTX)
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#endif

#if defined(HYDRO_PLATFORM_VULKAN)
#include <vulkan/vulkan.hpp>
#endif

#if defined(HYDRO_PLATFORM_OPENGL)
#include <glad/gl.h>
#endif

#include <cstring>
#include <cassert>
#include <vector>
#include <array>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <exception>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <format>
#include <glm/fwd.hpp>

#include <Jolt/Jolt.h>


