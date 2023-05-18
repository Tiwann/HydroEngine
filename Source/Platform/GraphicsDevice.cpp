#include "HydroPCH.h"
#include "GraphicsDevice.h"
#include "PlatformDevice.h"

namespace Hydro
{
    GraphicsDevice* GraphicsDevice::Create()
    {
        #if defined(HYDRO_PLATFORM_DIRECTX)
                return new DirectXDevice();
        #elif defined(HYDRO_PLATFORM_VULKAN)
                return new VulkanDevice();
        #elif defined(HYDRO_PLATFORM_OPENGL)
                return new OpenGLDevice();
        #endif
    }
}

