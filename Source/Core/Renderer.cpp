#include "HydroPCH.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLDevice.h"


namespace Hydro
{
    Renderer::Renderer(GraphicsDevice* device)
        : m_Device(device)
    {
    }

    Renderer::~Renderer()
    {
        delete m_Device;
    }

    void Renderer::Clear() const
    {
        #if defined(HYDRO_PLATFORM_DIRECTX)
        if(DirectXDevice* Device = (DirectXDevice*)m_Device.get())
        {
            Device->Clear();
        }
        #elif defined(HYDRO_PLATFORM_VULKAN)
        if(VulkanDevice* Device = (VulkanDevice*)m_Device.get())
        {
            Device->Clear();
        }
        #elif defined(HYDRO_PLATFORM_OPENGL)
        if(OpenGLDevice* Device = dynamic_cast<OpenGLDevice*>(m_Device))
        {
            Device->Clear();
        }
        #endif
        
    }

    void Renderer::Clear(Color color) const
    {
        m_Device->Clear(color);
    }

    void Renderer::SwapBuffers() const
    {
        m_Device->SwapBuffers();
    }
}
