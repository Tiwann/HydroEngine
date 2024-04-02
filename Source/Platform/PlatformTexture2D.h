#pragma once


#if defined(HYDRO_PLATFORM_OPENGL)
#include "OpenGL/OpenGLTexture2D.h"
#endif

#if defined(HYDRO_PLATFORM_VULKAN)
#include "Vulkan/VulkanTexture2D.h"
#endif

#if defined(HYDRO_PLATFORM_DIRECTX)
#include "DirectX/DirectXTexture2D.h"
#endif