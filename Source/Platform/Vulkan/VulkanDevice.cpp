#include "HydroPCH.h"
#include "VulkanDevice.h"

namespace Hydro
{
    VulkanDevice::VulkanDevice(): GraphicsDevice()
    {
        CreateInstance();
        SelectPhysicalDevice();
        CreateWindowSurface();
    }

    void VulkanDevice::ClearDepthBuffer()
    {
        
    }

    void VulkanDevice::ClearColor(Color color)
    {
            
    }

    void VulkanDevice::SwapBuffers()
    {
            
    }

    VkPhysicalDeviceProperties2 VulkanDevice::GetPhysicalDeviceProperties(const VkPhysicalDevice& Device)
    {
        VkPhysicalDeviceProperties2 properties2{};
        properties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        vkGetPhysicalDeviceProperties2(Device, &properties2);
        return properties2;
    }

    VkPhysicalDeviceFeatures2 VulkanDevice::GetPhysicalDeviceFeatures(const VkPhysicalDevice& Device)
    {
        VkPhysicalDeviceFeatures2 features2{};
        features2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
        vkGetPhysicalDeviceFeatures2(Device, &features2);
        return features2;
    }

    void VulkanDevice::CreateInstance()
    {
        Application& application = Application::GetCurrentApplication();
        uint32_t glfwExtensionsCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
            
        m_RequiredExtensions = { glfwExtensions, glfwExtensions + glfwExtensionsCount };
        m_RequiredExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
        
        VkApplicationInfo applicationCreateInfo{};
        applicationCreateInfo.apiVersion = VK_VERSION_1_3;
        applicationCreateInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationCreateInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
        applicationCreateInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationCreateInfo.pApplicationName = *application.GetSpecifications().AppName;

            
        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &applicationCreateInfo;
        instanceCreateInfo.enabledExtensionCount = (uint32_t)m_RequiredExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = m_RequiredExtensions.data();
        
        const VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
        if(result != VK_SUCCESS)
        {
            std::cerr << "Vulkan: Failed to create Vulkan Intsance!\n";
            application.RequireExit(false);
        }
    }

    void VulkanDevice::SelectPhysicalDevice()
    {
        uint32_t availablePhysicalDevicesCount = 0;
        vkEnumeratePhysicalDevices(m_instance, &availablePhysicalDevicesCount, nullptr);
        if(availablePhysicalDevicesCount == 0)
        {
            std::cerr << "Vulkan: No compatible physical devices found!\n";
            Application::GetCurrentApplication().RequireExit(false);
        }
        
        VkPhysicalDevice* availablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDevicesCount];
        vkEnumeratePhysicalDevices(m_instance, &availablePhysicalDevicesCount, availablePhysicalDevices);
        
        std::vector<VkPhysicalDevice> DiscreteGPUDevices;
        for(uint32_t i = 0; i < availablePhysicalDevicesCount; i++)
        {
            VkPhysicalDeviceProperties2 properties = GetPhysicalDeviceProperties(availablePhysicalDevices[i]);
            if(properties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                DiscreteGPUDevices.push_back(availablePhysicalDevices[i]);
            }
        }

        for(const VkPhysicalDevice& Device : DiscreteGPUDevices)
        {
            VkPhysicalDeviceFeatures2KHR features = GetPhysicalDeviceFeatures(Device);
            if(features.features.geometryShader)
            {
                m_PhysicalDevice = Device;
            }
        }

        delete[] availablePhysicalDevices;
    }

    void VulkanDevice::CreateWindowSurface()
    {
        const VkResult result = glfwCreateWindowSurface(m_instance, Application::GetCurrentApplication().GetWindow().GetNativeWindow(), nullptr, &m_Surface);
        if(result != VK_SUCCESS)
        {
            std::cerr << "Vulkan: Failed to create window surface\n";
            Application::GetCurrentApplication().RequireExit(false);
        }  
    }
}
