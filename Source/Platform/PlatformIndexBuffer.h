#pragma once

#if defined(HYDRO_PLATFORM_OPENGL)
#include "OpenGL/OpenGLIndexBuffer.h"
#endif

#if defined(HYDRO_PLATFORM_VULKAN)
#include "Vulkan/VulkanIndexBuffer.h"
#endif

#if defined(HYDRO_PLATFORM_DIRECTX)
#include "DirectX/DirectXIndexBuffer.h"
#endif