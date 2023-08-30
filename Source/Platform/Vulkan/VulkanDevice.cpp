#include "HydroPCH.h"
#include "VulkanDevice.h"
#include "Core/Log.h"
#include "Core/Application.h"
#include "Core/LogVerbosity.h"
#include <GLFW/glfw3.h>

namespace Hydro
{
    VulkanDevice::VulkanDevice() : RendererDevice()
    {
        HYDRO_LOG(Vulkan, Trace, "Initializing Vulkan...");
        if(!CreateInstance()) return;
        if(!SelectPhysicalDevice()) return;
        if(!CreateWindowSurface()) return;
        if(!CreateDevice()) return;
        if(!CreateSwapchain()) return;
        
        vk::PhysicalDeviceProperties2 properties = m_PhysicalDevice.getProperties2();
        HYDRO_LOG(Vulkan, Trace, "Using Vulkan 1.3");
        const std::string DeviceTypeString = GetGPUTypeString(properties.properties.deviceType);
        HYDRO_LOG(Vulkan, Trace, "Using: {}; GPU Type: {}", properties.properties.deviceName, DeviceTypeString);
        m_IsReady = true;
    }

    VulkanDevice::~VulkanDevice()
    {
        HYDRO_LOG(Vulkan, Trace, "Destroying swapchain...");
        m_Device.destroySwapchainKHR(m_Swapchain);

        HYDRO_LOG(Vulkan, Trace, "Destroying logical device...");
        m_Device.destroy();

        HYDRO_LOG(Vulkan, Trace, "Destroying Window surface...");
        m_instance.destroySurfaceKHR(m_Surface);

        HYDRO_LOG(Vulkan, Trace, "Destroying Vulkan instance...");
        m_instance.destroy();
    }

    void VulkanDevice::ClearDepthBuffer()
    {
        
    }

    void VulkanDevice::ClearColor(const Color& color)
    {
            
    }

    void VulkanDevice::SwapBuffers()
    {
            
    }

    void VulkanDevice::DrawIndexed()
    {
    }

    bool VulkanDevice::CreateInstance()
    {
        Application& application = Application::GetCurrentApplication();
        uint32_t glfwExtensionsCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
            
        m_InstanceExtensions = { glfwExtensions, glfwExtensions + glfwExtensionsCount };
        m_InstanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
        m_InstanceExtensions.push_back("VK_KHR_get_surface_capabilities2");

        vk::ApplicationInfo applicationInfo;
        applicationInfo.setApiVersion(VK_VERSION_1_3);
        applicationInfo.setEngineVersion(VK_MAKE_VERSION((HYDRO_VERSION_MAJ), (HYDRO_VERSION_MIN), 0));
        applicationInfo.setPApplicationName(application.GetConfiguration().AppName.c_str());
        
        vk::InstanceCreateInfo instanceCreateInfo;
        instanceCreateInfo.setPApplicationInfo(&applicationInfo);
        instanceCreateInfo.setEnabledExtensionCount((uint32_t)m_InstanceExtensions.size());
        instanceCreateInfo.setPpEnabledExtensionNames(m_InstanceExtensions.data());
        
        const vk::Result result = vk::createInstance(&instanceCreateInfo, nullptr, &m_instance);
        if(result != vk::Result::eSuccess)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to create Vulkan Intsance!");
            application.RequireExit(false);
            return false;
        }
        HYDRO_LOG(Vulkan, Info, "Vulkan instance created!");
        return true;
    }

    bool VulkanDevice::SelectPhysicalDevice()
    {
        std::vector<vk::PhysicalDevice> availableDevices = m_instance.enumeratePhysicalDevices();
        if(availableDevices.empty())
        {
            HYDRO_LOG(Vulkan, Error, "No compatible physical devices found!");
            Application::GetCurrentApplication().RequireExit(false);
            return false;
        }
        

        if(availableDevices.size() == 1)
        {
            m_PhysicalDevice = *availableDevices.begin();
        }
        else
        {
            
        }
        
        for(const auto& physicalDevice : availableDevices)
        {
            vk::PhysicalDeviceProperties2 properties2 = physicalDevice.getProperties2();
            vk::PhysicalDeviceFeatures2 features = physicalDevice.getFeatures2();
            if(properties2.properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && features.features.geometryShader)
            {
                m_PhysicalDevice = physicalDevice;
            }
        }
        HYDRO_LOG(Vulkan, Info, "Physical device selected!");
        return true;
    }

    bool VulkanDevice::CreateWindowSurface()
    {
        VkSurfaceKHR surface;
        const VkResult result = glfwCreateWindowSurface(m_instance, Application::GetCurrentApplication().GetWindow().GetNativeWindow(), nullptr, &surface);
        if(result != VK_SUCCESS)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to create window surface");
            Application::GetCurrentApplication().RequireExit(false);
            return false;
        }
        m_Surface = surface;
        HYDRO_LOG(Vulkan, Info, "Window surface created!");
        return true;
    }

    bool VulkanDevice::CreateDevice()
    {
        const std::vector<vk::QueueFamilyProperties> queueFamilies = m_PhysicalDevice.getQueueFamilyProperties();
        
        for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                m_GraphicsQueueIndex = i;
                break;
            }
        }

        for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
            if(const bool presentSupport = m_PhysicalDevice.getSurfaceSupportKHR(i, m_Surface))
            {
                m_PresentQueueIndex = i;
                break;
            }
        }
        
        if (!m_GraphicsQueueIndex.has_value()) {
            HYDRO_LOG(Vulkan, Error, "Failed to find a graphics queue family!");
            Application::GetCurrentApplication().RequireExit(false);
            return false;
        }

        if (!m_PresentQueueIndex.has_value()) {
            HYDRO_LOG(Vulkan, Error, "Failed to find a present queue family!");
            Application::GetCurrentApplication().RequireExit(false);
            return false;
        }
        
        // Create device
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        const bool sameQueueFamIndices = m_GraphicsQueueIndex.value() == m_PresentQueueIndex.value();
        const float queuePriorities[] = { 1.0f };
        if(sameQueueFamIndices)
        {
            const uint32_t queueFamilyIndex = m_GraphicsQueueIndex.value();
            vk::DeviceQueueCreateInfo queueCreateInfo;
            queueCreateInfo.setQueueCount(1);
            queueCreateInfo.setPQueuePriorities(queuePriorities);
            queueCreateInfo.setQueueFamilyIndex(queueFamilyIndex);
            queueCreateInfos.push_back(queueCreateInfo);
        }
        else
        {
            vk::DeviceQueueCreateInfo gfxQueueInfo;
            gfxQueueInfo.setQueueCount(1);
            gfxQueueInfo.setPQueuePriorities(queuePriorities);
            gfxQueueInfo.setQueueFamilyIndex(m_GraphicsQueueIndex.value());
            queueCreateInfos.push_back(gfxQueueInfo);
            
            vk::DeviceQueueCreateInfo prstQueueInfo;
            prstQueueInfo.setQueueCount(1);
            prstQueueInfo.setPQueuePriorities(queuePriorities);
            prstQueueInfo.setQueueFamilyIndex(m_PresentQueueIndex.value());
            queueCreateInfos.push_back(prstQueueInfo);
        }
        
        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.setQueueCreateInfoCount((uint32_t)queueCreateInfos.size());
        deviceCreateInfo.setPQueueCreateInfos(queueCreateInfos.data());
        m_DeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        deviceCreateInfo.setEnabledExtensionCount((uint32_t)m_DeviceExtensions.size());
        deviceCreateInfo.setPpEnabledExtensionNames(m_DeviceExtensions.data());
        m_Device = m_PhysicalDevice.createDevice(deviceCreateInfo);
        if(!m_Device)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to create logical device!");
            return false;
        }
        
        m_GraphicsQueue = m_Device.getQueue(m_GraphicsQueueIndex.value(), 0);
        if(!m_GraphicsQueue)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to retrieve Graphics Queue!");
            return false;
        }
        
        m_PresentQueue = m_Device.getQueue(m_PresentQueueIndex.value(), 0);
        if(!m_PresentQueue)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to retrieve Present Queue!");
            return false;
        }
        
        HYDRO_LOG(Vulkan, Info, "Logical device created!");
        return true;
    }

    bool VulkanDevice::CreateSwapchain()
    {
        const vk::PhysicalDeviceSurfaceInfo2KHR surfaceInfo(m_Surface);
        const auto formats = m_PhysicalDevice.getSurfaceFormats2KHR(surfaceInfo);
        const auto presentModes = m_PhysicalDevice.getSurfacePresentModesKHR(m_Surface);
        const auto capabilities = m_PhysicalDevice.getSurfaceCapabilities2KHR(surfaceInfo);
        const Application& application = Application::GetCurrentApplication();
        const GraphicsSettings& applicationGraphicsSettings = application.GetGraphicsSettings();
        
        vk::SwapchainCreateInfoKHR swapchainCreateInfo;
        swapchainCreateInfo.setSurface(m_Surface);
        swapchainCreateInfo.setImageFormat(m_Format = formats[0].surfaceFormat.format);
        swapchainCreateInfo.setImageColorSpace(formats[0].surfaceFormat.colorSpace);
        swapchainCreateInfo.setPresentMode(m_PresentMode = vk::PresentModeKHR::eFifo);
        swapchainCreateInfo.setClipped(true);
        swapchainCreateInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
        swapchainCreateInfo.setImageExtent(vk::Extent2D(application.GetWindow().GetWidth(), application.GetWindow().GetHeight()));
        swapchainCreateInfo.setMinImageCount(applicationGraphicsSettings.BufferType);
        swapchainCreateInfo.setImageArrayLayers(1);
        swapchainCreateInfo.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
        swapchainCreateInfo.setOldSwapchain(nullptr);

        const bool sameQueueFamilies = m_GraphicsQueueIndex.value() == m_PresentQueueIndex.value();
        const std::array queueFamilyIndices = { m_GraphicsQueueIndex.value(), m_PresentQueueIndex.value() };
        
        if (sameQueueFamilies) {
            swapchainCreateInfo.setImageSharingMode(vk::SharingMode::eConcurrent);
            swapchainCreateInfo.queueFamilyIndexCount = (uint32_t)queueFamilyIndices.size();
            swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
        } else {
            swapchainCreateInfo.setImageSharingMode(vk::SharingMode::eExclusive);
            swapchainCreateInfo.setQueueFamilyIndexCount(0);
            swapchainCreateInfo.setPQueueFamilyIndices(nullptr);
        }

        m_Swapchain = m_Device.createSwapchainKHR(swapchainCreateInfo);

        if(!m_Swapchain)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to create swapchain!");
            return false;
        }
        HYDRO_LOG(Vulkan, Info, "Swapchain created!");
        
        uint32_t SwapchainImageCount;
        vk::Result result = m_Device.getSwapchainImagesKHR(m_Swapchain, &SwapchainImageCount, nullptr);
        HYDRO_CHECK_VK_RESULT(result, "Failed to query swapchain images count");
        
        m_SwapchainImages.resize(SwapchainImageCount);
        result = m_Device.getSwapchainImagesKHR(m_Swapchain, &SwapchainImageCount, m_SwapchainImages.data());
        HYDRO_CHECK_VK_RESULT(result, "Failed to retrieve swapchain images");
        return true;
    }
    

    std::string VulkanDevice::GetGPUTypeString(const vk::PhysicalDeviceType& DeviceType) const
    {
        switch (DeviceType)
        {
        case vk::PhysicalDeviceType::eCpu:              return "CPU";
        case vk::PhysicalDeviceType::eOther:            return "Other";
        case vk::PhysicalDeviceType::eIntegratedGpu:    return "Integrated GPU";
        case vk::PhysicalDeviceType::eDiscreteGpu:      return "Discrete GPU";
        case vk::PhysicalDeviceType::eVirtualGpu:       return "Virtual GPU";
        }
        return "Unknown";
    }
}
