#pragma once

#if defined(HYDRO_PLATFORM_OPENGL)
#include "OpenGL/OpenGLVertexBuffer.h"
#endif

#if defined(HYDRO_PLATFORM_VULKAN)
#include "Vulkan/VulkanVertexBuffer.h"
#endif

#if defined(HYDRO_PLATFORM_DIRECTX)
#include "DirectX/DirectXVertexBuffer.h"
#endif