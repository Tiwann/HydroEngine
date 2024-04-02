#pragma once

#if defined(HYDRO_PLATFORM_OPENGL)
#include "OpenGL/OpenGLVertexArray.h"
#endif

#if defined(HYDRO_PLATFORM_VULKAN)
#include "Vulkan/VulkanVertexArray.h"
#endif

#if defined(HYDRO_PLATFORM_DIRECTX)
#include "DirectX/DirectXVertexArray.h"
#endif