#pragma once
#include <stdexcept>
#include <vector>

#include "HydroPCH.h"
#include "Platform/GraphicsDevice.h"
#include "Core/Application.h"

namespace Hydro
{
    class HYDRO_API VulkanDevice : public GraphicsDevice
    {
    public:
        VulkanDevice(Application& application) : GraphicsDevice(application)
        {

            uint32_t glfwExtensionsCount = 0;
            const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
            
            std::vector<const char*> requiredExtensions{ glfwExtensions, glfwExtensions + glfwExtensionsCount };
            requiredExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

            
            VkApplicationInfo applicationInfo{};
            applicationInfo.apiVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
            applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
            applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            applicationInfo.pApplicationName = *m_Application.GetSpecifications().AppName;

            
            VkInstanceCreateInfo instanceCreateInfo{};
            instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            instanceCreateInfo.pApplicationInfo = &applicationInfo;
            instanceCreateInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
            instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
            VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
            if(result != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to create Vulkan Intsance!");
            }

            uint32_t availablePhysicalDevicesCount = 0;
            vkEnumeratePhysicalDevices(m_instance, &availablePhysicalDevicesCount, nullptr);
            if(availablePhysicalDevicesCount == 0)
            {
                throw std::runtime_error("Vulkan: No compatible physical devices found!\n");
            }
            
            VkPhysicalDevice* availablePhysicalDevices = new VkPhysicalDevice[availablePhysicalDevicesCount];
            vkEnumeratePhysicalDevices(m_instance, &availablePhysicalDevicesCount, availablePhysicalDevices);
            
            
            for(uint32_t i = 0; i < availablePhysicalDevicesCount; i++)
            {
                VkPhysicalDeviceProperties2 properties{};
                properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
                vkGetPhysicalDeviceProperties2(availablePhysicalDevices[i], &properties);
                if(properties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                {
                    m_PhysicalDeviceProperties = properties;
                    m_PhysicalDevice = availablePhysicalDevices[i];
                }
            }
            

            VkDeviceCreateInfo deviceCreateInfo{};
            deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            //deviceCreateInfo.

            
            //vkCreateDevice(m_PhysicalDevice, )
            delete[] availablePhysicalDevices;
        }

    private:
        VkInstance m_instance{nullptr};
        VkPhysicalDevice m_PhysicalDevice{nullptr};
        VkPhysicalDeviceProperties2 m_PhysicalDeviceProperties{};
        VkDevice m_Device{nullptr};
    };
}
