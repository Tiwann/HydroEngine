#include "HydroPCH.h"
#include "GraphicsDevice.h"
#include "PlatformDevice.h"

namespace Hydro
{
    GraphicsDevice::GraphicsDevice(Application& application) :
        m_Application(application)
    {
    }

    GraphicsDevice* GraphicsDevice::Create(Application& Application)
    {
        #if defined(HYDRO_PLATFORM_DIRECTX)
                return new DirectXDevice(Application);
        #elif defined(HYDRO_PLATFORM_VULKAN)
                return new VulkanDevice(Application);
        #elif defined(HYDRO_PLATFORM_OPENGL)
                return new OpenGLDevice(Application);
        #endif
    }

    
}

