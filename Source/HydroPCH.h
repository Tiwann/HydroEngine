#pragma once

#if defined(HYDRO_PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(HYDRO_PLATFORM_UNIX)
	#include <unistd.h>
#endif


#if defined(HYDRO_PLATFORM_WINDOWS)
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#endif
#include <vulkan/vulkan.hpp>
#include <glad/gl.h>


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


