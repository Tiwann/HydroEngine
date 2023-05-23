#pragma once
#include "HydroPCH.h"
#include "Platform/RendererDevice.h"
#include "Core/Application.h"

namespace Hydro
{
    class HYDRO_API VulkanDevice : public RendererDevice
    {
    public:
        
        VulkanDevice();
        ~VulkanDevice() override;

        void ClearDepthBuffer() override;
        void ClearColor(Color color) override;
        void SwapBuffers() override;
        void DrawIndexed() override;
    

    private:
        vk::Instance             m_instance{nullptr};
        vk::PhysicalDevice       m_PhysicalDevice{nullptr};
        vk::SurfaceKHR           m_Surface{nullptr};
        vk::Device               m_Device{nullptr};
        vk::Queue                m_GraphicsQueue{nullptr};
        vk::Queue                m_PresentQueue{nullptr};
        std::vector<const char*> m_InstanceExtensions{};
        std::vector<const char*> m_DeviceExtensions{};
        std::optional<uint32_t>  m_GraphicsQueueIndex;
        std::optional<uint32_t>  m_PresentQueueIndex;
        vk::PresentModeKHR       m_PresentMode{vk::PresentModeKHR::eFifo};
        vk::SwapchainKHR         m_Swapchain{nullptr};
        std::vector<vk::Image>   m_SwapchainImages;

    private:
        bool CreateInstance();
        bool SelectPhysicalDevice();
        bool CreateWindowSurface();
        bool CreateDevice();
        bool CreateSwapchain();

        String GetGPUTypeString(const vk::PhysicalDeviceType& DeviceType) const;

    protected:
        using Super = RendererDevice;
    };
}
