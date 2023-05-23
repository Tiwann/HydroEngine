#include "HydroPCH.h"
#include "RendererDevice.h"
#include "PlatformDevice.h"

namespace Hydro
{
    RendererDevice* RendererDevice::Create()
    {
        #if defined(HYDRO_PLATFORM_DIRECTX)
                return new DirectXDevice();
        #elif defined(HYDRO_PLATFORM_VULKAN)
                return new VulkanDevice();
        #elif defined(HYDRO_PLATFORM_OPENGL)
                return new OpenGLDevice();
        #endif
    }

    bool RendererDevice::IsReady() const
    {
        return m_IsReady;
    }
}

