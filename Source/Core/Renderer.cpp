#include "HydroPCH.h"
#include "Renderer.h"
#include "Platform/PlatformDevice.h"


namespace Hydro
{
    Renderer::Renderer(RendererDevice* device)
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
        if(DirectXDevice* Device = dynamic_cast<DirectXDevice*>(m_Device))
        {
            Device->ClearDepthBuffer();
        }
        #elif defined(HYDRO_PLATFORM_VULKAN)
        if(VulkanDevice* Device = dynamic_cast<VulkanDevice*>(m_Device))
        {
            Device->ClearDepthBuffer();
        }
        #elif defined(HYDRO_PLATFORM_OPENGL)
        if(OpenGLDevice* Device = dynamic_cast<OpenGLDevice*>(m_Device))
        {
            Device->ClearDepthBuffer();
        }
        #endif
    }

    void Renderer::Clear(Color color) const
    {
        m_Device->ClearColor(color);
    }

    void Renderer::SwapBuffers() const
    {
        m_Device->SwapBuffers();
    }

    bool Renderer::IsReady() const
    {
        return m_Device->IsReady();
    }
}
