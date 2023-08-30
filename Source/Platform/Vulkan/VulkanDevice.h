#pragma once
#include "Macros.h"
#include "Platform/RendererDevice.h"
#include "Core/LogCategory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Vulkan, "VULKAN");

#define VK_FAILED(Res) (((vk::Result)(Res)) != vk::Result::eSuccess)

#define HYDRO_CHECK_VK_RESULT(Result, Message) \
    if(VK_FAILED(Result)) \
    { \
        HYDRO_LOG(Vulkan, Error, Message); \
        return false; \
    } ((void)0)
   

namespace vk
{
    class Instance;
    class PhysicalDevice;
    class SurfaceKHR;
    class Device;
    class Queue;
    enum class PresentModeKHR;
    class SwapchainKHR;
    class Image;
}

namespace Hydro
{
    class HYDRO_API VulkanDevice : public RendererDevice
    {
    public:
        
        VulkanDevice();
        ~VulkanDevice() override;

        void ClearDepthBuffer() override;
        void ClearColor(const Color& color) override;
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
        vk::Format               m_Format{vk::Format::eUndefined};
        vk::SwapchainKHR         m_Swapchain{nullptr};
        std::vector<vk::Image>   m_SwapchainImages;
        std::vector<vk::ImageView> m_SwapchainImagesViews;

    private:
        bool CreateInstance();
        bool SelectPhysicalDevice();
        bool CreateWindowSurface();
        bool CreateDevice();
        bool CreateSwapchain();
        std::string GetGPUTypeString(const vk::PhysicalDeviceType& DeviceType) const;

    protected:
        using Super = RendererDevice;
    };
}
