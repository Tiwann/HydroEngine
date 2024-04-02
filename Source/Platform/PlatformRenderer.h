#pragma once

#if defined(HYDRO_PLATFORM_OPENGL)
#include "OpenGL/OpenGLRendererBackend.h"
#endif

#if defined(HYDRO_PLATFORM_VULKAN)
#include "Vulkan/VulkanRenderer.h"
#endif

#if defined(HYDRO_PLATFORM_DIRECTX)
#include "DirectX/DirectXRenderer.h"
#endif
