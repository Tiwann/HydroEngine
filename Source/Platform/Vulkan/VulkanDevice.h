#pragma once
#include "HydroPCH.h"
#include "Platform/GraphicsDevice.h"
#include "Core/Application.h"

namespace Hydro
{
    class HYDRO_API VulkanDevice : public GraphicsDevice
    {
    public:
        VulkanDevice();

        void ClearDepthBuffer() override;
        void ClearColor(Color color) override;
        void SwapBuffers() override;

    private:
        VkInstance               m_instance{nullptr};
        VkPhysicalDevice         m_PhysicalDevice{nullptr};
        VkSurfaceKHR             m_Surface{nullptr};
        std::vector<const char*> m_RequiredExtensions{};

    private:
        VkPhysicalDeviceProperties2 GetPhysicalDeviceProperties(const VkPhysicalDevice& Device);
        VkPhysicalDeviceFeatures2 GetPhysicalDeviceFeatures(const VkPhysicalDevice& Device);
        void CreateInstance();
        void SelectPhysicalDevice();
        void CreateWindowSurface();
    };
}
