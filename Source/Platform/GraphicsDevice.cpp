#include "HydroPCH.h"
#include "GraphicsDevice.h"
#include "DirectX/DirectXDevice.h"
#include "OpenGL/OpenGLDevice.h"
#include "Vulkan/VulkanDevice.h"

namespace Hydro
{
    GraphicsDevice::GraphicsDevice(Application& application) :
        m_Application(application)
    {
    }

    GraphicsDevice* GraphicsDevice::Create(Application& Application)
    {
        #if defined(HYDRO_PLATFORM_DIRECTX)
                return DirectXDevice(Application);
        #elif defined(HYDRO_PLATFORM_VULKAN)
                return VulkanDevice(Application);
        #elif defined(HYDRO_PLATFORM_OPENGL)
                return new OpenGLDevice(Application);
        #endif
    }

    
}

