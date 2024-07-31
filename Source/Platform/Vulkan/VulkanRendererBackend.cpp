#include "HydroPCH.h"
#include "VulkanRendererBackend.h"
#include "Core/Log.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Core/LogVerbosity.h"

#include <GLFW/glfw3.h>

#include "Components/Rendering/Renderer.h"
#include "Core/Vertex.h"

#define HYDRO_VULKAN_ERROR(str, ...) HYDRO_LOG(Vulkan, Error, str, __VA_ARGS__)
#define HYDRO_VULKAN_SUCCESS(str, ...) HYDRO_LOG(Vulkan, Info, str, __VA_ARGS__)

namespace Hydro
{
    VulkanRendererBackend::VulkanRendererBackend(Application* Owner) : RendererBackend(Owner)
    {
        
    }

    VulkanRendererBackend::~VulkanRendererBackend()
    {
        
    }

    bool VulkanRendererBackend::Initialize()
    {
        HYDRO_LOG(Vulkan, Trace, "Initializing Vulkan...");
        if(!CreateInstance()) return false;
        if(!SelectPhysicalDevice()) return false;
        if(!CreateWindowSurface()) return false;
        if(!CreateDevice()) return false;
        if(!CreateSwapchain()) return false;
        if(!CreateSemaphores()) return false;
        if(!CreateCommandPool()) return false;
        if(!CreateRenderPass()) return false;
        if(!CreateFramebuffers()) return false;
        //if(!CreateGraphicsPipeline()) return false;
        
        vk::PhysicalDeviceProperties2 properties = m_PhysicalDevice.getProperties2();
        HYDRO_LOG(Vulkan, Trace, "Using Vulkan 1.3");
        HYDRO_LOG(Vulkan, Trace, "Using: {}", properties.properties.deviceName);
        return true;
    }

    void VulkanRendererBackend::Destroy()
    {
        HYDRO_LOG(Vulkan, Trace, "Freeing memory");
        for(const auto& Memory : m_Memories)
            m_Device.free(Memory);
        
        HYDRO_LOG(Vulkan, Trace, "Destroying Texture Images");
        for(const auto& Image : m_TextureImages)
            m_Device.destroyImage(Image);
        
        HYDRO_LOG(Vulkan, Trace, "Destroying Renderpass");
        m_Device.destroyRenderPass(m_RenderPass);

        HYDRO_LOG(Vulkan, Trace, "Destroying Renderpass");
        for(const auto& Framebuffer : m_Framebuffers)
            m_Device.destroyFramebuffer(Framebuffer);
        
        
        HYDRO_LOG(Vulkan, Trace, "Destroying command pool...");
        m_Device.destroy(m_CommandPool);
        
        HYDRO_LOG(Vulkan, Trace, "Destroying semaphores...");
        m_Device.destroy(m_PresentSemaphore);
        m_Device.destroy(m_SubmitSemaphore);
        m_Device.destroy(m_AcquireImageSemaphore);
        

        HYDRO_LOG(Vulkan, Trace, "Destroying Image views...");
        for(const auto& ImageView : m_SwapchainImagesViews)
            m_Device.destroy(ImageView);


        HYDRO_LOG(Vulkan, Trace, "Destroying swapchain...");
        m_Device.destroy(m_Swapchain);
        
        HYDRO_LOG(Vulkan, Trace, "Destroying logical device...");
        m_Device.destroy();

        HYDRO_LOG(Vulkan, Trace, "Destroying Window surface...");
        m_Instance.destroySurfaceKHR(m_Surface);

        HYDRO_LOG(Vulkan, Trace, "Destroying Debug Messenger...");
        PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugMessenger
        = (PFN_vkDestroyDebugUtilsMessengerEXT)m_Instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT");
        
        if(!vkDestroyDebugMessenger)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to retrieve function pointer: vkDestroyDebugMessenger");
            return;
        }
        vkDestroyDebugMessenger(m_Instance, m_DebugMessenger, nullptr);
        
        

        HYDRO_LOG(Vulkan, Trace, "Destroying Vulkan instance...");
        m_Instance.destroy();
    }

    void VulkanRendererBackend::ClearDepthBuffer()
    {
        //const uint32_t CurrentImage = GetNextSwapchainImage();
        
        
    }

    void VulkanRendererBackend::ClearColor(const Color& color)
    {
        const uint32_t CurrentImage = GetNextSwapchainImage();

        vk::CommandBufferAllocateInfo AllocateInfo{};
        AllocateInfo.setCommandBufferCount(1);
        AllocateInfo.setLevel(vk::CommandBufferLevel::ePrimary);
        AllocateInfo.setCommandPool(m_CommandPool);
        const vk::CommandBuffer Command = m_Device.allocateCommandBuffers(AllocateInfo).at(0);
        
        vk::CommandBufferBeginInfo BeginInfo{};
        BeginInfo.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
        
            Command.begin(BeginInfo);

            vk::RenderPassBeginInfo RenderPassBeginInfo{};
            RenderPassBeginInfo.setRenderPass(m_RenderPass);
            const Window& Window = m_Application.GetWindow();
            const vk::Extent2D RenderExtent = {Window.GetWidth<uint32_t>(), Window.GetHeight<uint32_t>()};
            const vk::Rect2D RenderArea({0, 0}, RenderExtent);
            RenderPassBeginInfo.setRenderArea(RenderArea);
            RenderPassBeginInfo.setFramebuffer(m_Framebuffers[CurrentImage]);
            const vk::ClearValue ClearValue{{color.r, color.g, color.b, color.a}};
            RenderPassBeginInfo.setClearValueCount(1);
            RenderPassBeginInfo.setClearValues(ClearValue);
            Command.beginRenderPass(RenderPassBeginInfo, vk::SubpassContents::eInline);

            Command.endRenderPass();
            Command.end();
        
        vk::SubmitInfo SubmitInfo{};
        const vk::PipelineStageFlags& Flags = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        SubmitInfo.setWaitDstStageMask(Flags);
        SubmitInfo.setCommandBufferCount(1);
        SubmitInfo.setCommandBuffers(Command);
        SubmitInfo.setSignalSemaphores(m_SubmitSemaphore);
        SubmitInfo.setWaitSemaphores(m_AcquireImageSemaphore);
        m_GraphicsQueue.submit(SubmitInfo);
        
        vk::PresentInfoKHR PresentInfo{};
        PresentInfo.setSwapchains(m_Swapchain);
        PresentInfo.setImageIndices(CurrentImage);
        PresentInfo.setWaitSemaphores(m_SubmitSemaphore);
        const vk::Result Result = m_PresentQueue.presentKHR(PresentInfo);
        if(Result != vk::Result::eSuccess)
        {
            HYDRO_VULKAN_ERROR("Failed to present! Clear Color failed.");
        }

        
        m_Device.waitIdle();
        m_Device.freeCommandBuffers(m_CommandPool, Command);
    }

    void VulkanRendererBackend::SwapBuffers()
    {
            
    }

    vk::Image VulkanRendererBackend::CreateImage(const vk::ImageCreateInfo& CreateInfo)
    {
        const auto Image = m_Device.createImage(CreateInfo);
        m_TextureImages.push_back(Image);
        return Image;
    }

    vk::DeviceMemory VulkanRendererBackend::AllocateMemory(const vk::MemoryAllocateInfo& AllocateInfo)
    {
        const auto Memory = m_Device.allocateMemory(AllocateInfo);
        m_Memories.push_back(Memory);
        return Memory;
    }

    void VulkanRendererBackend::FreeMemory(const vk::DeviceMemory& Memory) const
    {
        m_Device.free(Memory);
    }


    vk::Device VulkanRendererBackend::GetDevice() const
    {
        return m_Device;
    }

    vk::Instance VulkanRendererBackend::GetInstance() const
    {
        return m_Instance;
    }

    vk::PhysicalDevice VulkanRendererBackend::GetPhysicalDevice() const
    {
        return m_PhysicalDevice;
    }

    vk::Queue VulkanRendererBackend::GetGraphicsQueue() const
    {
        return m_GraphicsQueue;
    }

    uint32_t VulkanRendererBackend::GetImageCount() const
    {
        return m_ImageCount;
    }

    uint32_t VulkanRendererBackend::GetGraphicsQueueFamilyIndex() const
    {
        return m_GraphicsQueueIndex.value_or(0);
    }

    void VulkanRendererBackend::DrawIndexed(const Vao& VAO, const Vbo& VBO, const Ibo& IBO, const Ref<Shader>& Shader)
    {
    }

    void VulkanRendererBackend::SetCullMode(CullMode Mode)
    {
        RendererBackend::SetCullMode(Mode);
    }


#if defined(HYDRO_DEBUG)
    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugMessageCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT,
            const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
            void*)
    {
        const auto MessageSeverity = (vk::DebugUtilsMessageSeverityFlagBitsEXT)messageSeverity;
        if(MessageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError)
        {
            HYDRO_LOG(Vulkan, Error, pCallbackData->pMessage);
            return false;
        }

        if(MessageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning)
        {
            HYDRO_LOG(Vulkan, Warning, pCallbackData->pMessage);
            return false;
        }
        return true;
    }
#endif
    
    bool VulkanRendererBackend::CreateInstance()
    {
        uint32_t glfwExtensionsCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
        
        
        m_InstanceExtensions = { glfwExtensions, glfwExtensions + glfwExtensionsCount };
        m_InstanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
        m_InstanceExtensions.push_back(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);
#if defined(HYDRO_DEBUG)
        m_InstanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        m_Layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

        vk::ApplicationInfo applicationInfo;
        applicationInfo.setApiVersion(VK_API_VERSION_1_3);
        applicationInfo.setEngineVersion(VK_MAKE_VERSION((HYDRO_VERSION_MAJ), (HYDRO_VERSION_MIN), 0));
        applicationInfo.setPApplicationName(m_Application.GetConfiguration().AppName.c_str());
        
        vk::InstanceCreateInfo instanceCreateInfo;
        instanceCreateInfo.setPApplicationInfo(&applicationInfo);
        instanceCreateInfo.setEnabledExtensionCount((uint32_t)m_InstanceExtensions.size());
        instanceCreateInfo.setPpEnabledExtensionNames(m_InstanceExtensions.data());
        instanceCreateInfo.setEnabledLayerCount((uint32_t)m_Layers.size());
        instanceCreateInfo.setPpEnabledLayerNames(m_Layers.data());
        
        m_Instance = vk::createInstance(instanceCreateInfo);
        if(!m_Instance)
        {
            HYDRO_VULKAN_ERROR("Failed to create Vulkan Intsance!");
            m_Application.RequireExit();
            return false;
        }
        HYDRO_LOG(Vulkan, Info, "Vulkan instance created!");

#if defined(HYDRO_DEBUG)
        vk::DebugUtilsMessengerCreateInfoEXT DebugMessengerCreateInfo{};
        
        const auto SeverityFlags = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning;
        DebugMessengerCreateInfo.setMessageSeverity(SeverityFlags);

        const auto TypeFlags = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
        | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
        DebugMessengerCreateInfo.setMessageType(TypeFlags);
        
        DebugMessengerCreateInfo.setPfnUserCallback(VulkanDebugMessageCallback);
        
        const PFN_vkCreateDebugUtilsMessengerEXT VkCreateDebugUtilsMessengerExt = (PFN_vkCreateDebugUtilsMessengerEXT)m_Instance.getProcAddr("vkCreateDebugUtilsMessengerEXT");
        const VkResult Result = VkCreateDebugUtilsMessengerExt(m_Instance, (const VkDebugUtilsMessengerCreateInfoEXT*)&DebugMessengerCreateInfo, nullptr, (VkDebugUtilsMessengerEXT*)&m_DebugMessenger);
        if(Result != VK_SUCCESS)
        {
            HYDRO_VULKAN_ERROR("Failed to create debug messenger!");
            return false;
        }
#endif
        return true;
    }

    bool VulkanRendererBackend::SelectPhysicalDevice()
    {
        std::vector<vk::PhysicalDevice> availableDevices = m_Instance.enumeratePhysicalDevices();
        if(availableDevices.empty())
        {
            HYDRO_VULKAN_ERROR("No compatible physical devices found!");
            m_Application.RequireExit();
            return false;
        }
        

        if(availableDevices.size() == 1)
        {
            m_PhysicalDevice = *availableDevices.begin();
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

    bool VulkanRendererBackend::CreateWindowSurface()
    {
        VkSurfaceKHR surface;
        GLFWwindow* Window = m_Application.GetWindow().GetNativeWindow();
        const VkResult result = glfwCreateWindowSurface(m_Instance, Window, nullptr, &surface);
        if(result != VK_SUCCESS)
        {
            HYDRO_VULKAN_ERROR("Failed to create window surface");
            m_Application.RequireExit();
            return false;
        }
        m_Surface = surface;
        HYDRO_LOG(Vulkan, Info, "Window surface created!");
        return true;
    }

    bool VulkanRendererBackend::CreateDevice()
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
            if(m_PhysicalDevice.getSurfaceSupportKHR(i, m_Surface))
            {
                m_PresentQueueIndex = i;
                break;
            }
        }
        
        if (!m_GraphicsQueueIndex.has_value()) {
            HYDRO_LOG(Vulkan, Error, "Failed to find a graphics queue family!");
            m_Application.RequireExit();
            return false;
        }

        if (!m_PresentQueueIndex.has_value()) {
            HYDRO_LOG(Vulkan, Error, "Failed to find a present queue family!");
            m_Application.RequireExit();
            return false;
        }
        
        // Create device
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
        const bool sameQueueFamIndices = m_GraphicsQueueIndex.value() == m_PresentQueueIndex.value();
        static constexpr float queuePriorities[] = { 1.0f };
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

    bool VulkanRendererBackend::CreateSwapchain()
    {
        const vk::PhysicalDeviceSurfaceInfo2KHR surfaceInfo(m_Surface);
        const auto formats = m_PhysicalDevice.getSurfaceFormats2KHR(surfaceInfo);
        const auto presentModes = m_PhysicalDevice.getSurfacePresentModesKHR(m_Surface);
        const GraphicsSettings& applicationGraphicsSettings = m_Application.GetGraphicsSettings();
        const Window& Window = m_Application.GetWindow();
        
        vk::SwapchainCreateInfoKHR swapchainCreateInfo;
        swapchainCreateInfo.setSurface(m_Surface);
        swapchainCreateInfo.setImageFormat(m_Format = formats[0].surfaceFormat.format);
        swapchainCreateInfo.setImageColorSpace(formats[0].surfaceFormat.colorSpace);
        swapchainCreateInfo.setPresentMode(m_PresentMode = vk::PresentModeKHR::eFifo);
        swapchainCreateInfo.setClipped(true);
        swapchainCreateInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
        swapchainCreateInfo.setImageExtent(vk::Extent2D(Window.GetWidth<uint32_t>(), Window.GetHeight<uint32_t>()));
        swapchainCreateInfo.setMinImageCount(applicationGraphicsSettings.BufferType);
        swapchainCreateInfo.setImageArrayLayers(1);
        swapchainCreateInfo.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
        swapchainCreateInfo.setOldSwapchain(nullptr);
        
        /*const bool sameQueueFamilies = m_GraphicsQueueIndex.value() == m_PresentQueueIndex.value();
        const std::array queueFamilyIndices = { m_GraphicsQueueIndex.value(), m_PresentQueueIndex.value() };
        
        if (sameQueueFamilies) {
            swapchainCreateInfo.setImageSharingMode(vk::SharingMode::eExclusive);
            swapchainCreateInfo.setQueueFamilyIndexCount(1);
            swapchainCreateInfo.setPQueueFamilyIndices(queueFamilyIndices.data());
        } else {
            swapchainCreateInfo.setImageSharingMode(vk::SharingMode::eExclusive);
            swapchainCreateInfo.setQueueFamilyIndexCount(queueFamilyIndices.size());
            swapchainCreateInfo.setPQueueFamilyIndices(queueFamilyIndices.data());
        }*/

        m_Swapchain = m_Device.createSwapchainKHR(swapchainCreateInfo);

        if(!m_Swapchain)
        {
            HYDRO_LOG(Vulkan, Error, "Failed to create swapchain!");
            return false;
        }
        HYDRO_LOG(Vulkan, Info, "Swapchain created!");
        
        vk::Result result = m_Device.getSwapchainImagesKHR(m_Swapchain, &m_ImageCount, nullptr);
        HYDRO_CHECK_VK_RESULT(result, "Failed to query swapchain images count");
        
        m_SwapchainImages.resize(m_ImageCount);
        result = m_Device.getSwapchainImagesKHR(m_Swapchain, &m_ImageCount, m_SwapchainImages.data());
        HYDRO_CHECK_VK_RESULT(result, "Failed to retrieve swapchain images");


        // IMAGES VIEWS
        m_SwapchainImagesViews.resize(m_ImageCount);
        for (size_t i = 0; i < m_ImageCount; i++) {
            
            vk::ImageViewCreateInfo ImageViewsCreateInfo;
            ImageViewsCreateInfo.setImage(m_SwapchainImages[i]);
            ImageViewsCreateInfo.setViewType(vk::ImageViewType::e2D);
            ImageViewsCreateInfo.setFormat(m_Format);
            
            vk::ImageSubresourceRange ImageSubresourceRange;
            ImageSubresourceRange.setAspectMask(vk::ImageAspectFlagBits::eColor);
            ImageSubresourceRange.setLevelCount(1);
            ImageSubresourceRange.setLayerCount(1);
            ImageViewsCreateInfo.setSubresourceRange(ImageSubresourceRange);

            m_SwapchainImagesViews[i] = m_Device.createImageView(ImageViewsCreateInfo);
            if(!m_SwapchainImagesViews[i])
            {
                HYDRO_VULKAN_ERROR("Failed to create swapchain image view!");
                return false;
            }
        }

        HYDRO_LOG(Vulkan, Info, "Successfully created {} swapchain image views!", m_SwapchainImagesViews.size());
        return true;
    }

    bool VulkanRendererBackend::CreateSemaphores()
    {
        constexpr vk::SemaphoreCreateInfo CreateInfo{};
        m_AcquireImageSemaphore = m_Device.createSemaphore(CreateInfo);
        if(!m_AcquireImageSemaphore)
        {
            HYDRO_VULKAN_ERROR("Failed to create AcquireImage Semaphore!");
            return false;
        }
        
        m_SubmitSemaphore = m_Device.createSemaphore(CreateInfo);
        if(!m_AcquireImageSemaphore)
        {
            HYDRO_VULKAN_ERROR("Failed to create QueueSubmit Semaphore!");
            return false;
        }
        
        m_PresentSemaphore = m_Device.createSemaphore(CreateInfo);
        if(!m_AcquireImageSemaphore)
        {
            HYDRO_VULKAN_ERROR("Failed to create Present Semaphore!");
            return false;
        }

        return true;
    }

    bool VulkanRendererBackend::CreateGraphicsPipeline()
    {
        vk::PipelineColorBlendAttachmentState ColorAttachment;
        ColorAttachment.setBlendEnable(false);
        ColorAttachment.setColorWriteMask(
            vk::ColorComponentFlagBits::eR |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eA);
        
        vk::PipelineColorBlendStateCreateInfo ColorBlendState{};
        ColorBlendState.setAttachments(ColorAttachment);
        ColorBlendState.setAttachmentCount(1);

        vk::VertexInputAttributeDescription PositionAttributeDescription{};
        PositionAttributeDescription.setBinding(0);
        PositionAttributeDescription.setLocation(0);
        PositionAttributeDescription.setFormat(vk::Format::eR32G32B32Sfloat);
        PositionAttributeDescription.setOffset(offsetof(Vertex, Position));

        vk::VertexInputAttributeDescription TexCoordAttributeDescription{};
        PositionAttributeDescription.setBinding(1);
        PositionAttributeDescription.setLocation(1);
        PositionAttributeDescription.setFormat(vk::Format::eR32G32Sfloat);
        PositionAttributeDescription.setOffset(offsetof(Vertex, Position));

        vk::VertexInputAttributeDescription NormalAttributeDescription{};
        PositionAttributeDescription.setBinding(2);
        PositionAttributeDescription.setLocation(2);
        PositionAttributeDescription.setFormat(vk::Format::eR32G32B32Sfloat);
        PositionAttributeDescription.setOffset(offsetof(Vertex, Position));

        vk::VertexInputAttributeDescription ColorAttributeDescription{};
        PositionAttributeDescription.setBinding(3);
        PositionAttributeDescription.setLocation(3);
        PositionAttributeDescription.setFormat(vk::Format::eR32G32B32A32Sfloat);
        PositionAttributeDescription.setOffset(offsetof(Vertex, Position));

        const std::array VertexAttributeDescriptions
        {
            PositionAttributeDescription,
            TexCoordAttributeDescription,
            NormalAttributeDescription,
            ColorAttributeDescription
        };

        vk::VertexInputBindingDescription PositionBindingDescription{};
        PositionBindingDescription.setBinding(0);
        PositionBindingDescription.setStride(sizeof(Vertex));
        PositionBindingDescription.setInputRate(vk::VertexInputRate::eVertex);

        vk::VertexInputBindingDescription TexCoordBindingDescription{};
        TexCoordBindingDescription.setBinding(1);
        TexCoordBindingDescription.setStride(sizeof(Vertex));
        TexCoordBindingDescription.setInputRate(vk::VertexInputRate::eVertex);

        vk::VertexInputBindingDescription NormalBindingDescription{};
        NormalBindingDescription.setBinding(2);
        NormalBindingDescription.setStride(sizeof(Vertex));
        NormalBindingDescription.setInputRate(vk::VertexInputRate::eVertex);

        vk::VertexInputBindingDescription ColorBindingDescription{};
        ColorBindingDescription.setBinding(3);
        ColorBindingDescription.setStride(sizeof(Vertex));
        ColorBindingDescription.setInputRate(vk::VertexInputRate::eVertex);

        const std::array BindingDescriptions
        {
            PositionBindingDescription,
            TexCoordBindingDescription,
            NormalBindingDescription,
            ColorBindingDescription
        };
        
        vk::PipelineVertexInputStateCreateInfo VertexInputState{};
        VertexInputState.setVertexAttributeDescriptions(VertexAttributeDescriptions);
        VertexInputState.setVertexAttributeDescriptionCount(std::size(VertexAttributeDescriptions));
        VertexInputState.setVertexBindingDescriptions(BindingDescriptions);
        VertexInputState.setVertexBindingDescriptionCount(std::size(BindingDescriptions));
        
        vk::PipelineRasterizationStateCreateInfo RasterizationState{};
        RasterizationState.setCullMode(ConvertCullMode(m_CullMode));
        RasterizationState.setFrontFace(vk::FrontFace::eClockwise);
        RasterizationState.setPolygonMode(vk::PolygonMode::eFill);
        RasterizationState.setRasterizerDiscardEnable(true);
        RasterizationState.setLineWidth(1.0f);
        
        vk::PipelineViewportStateCreateInfo ViewportState{};
        const Window& Window = m_Application.GetWindow();
        const vk::Rect2D ViewportRect({0, 0}, {Window.GetWidth<uint32_t>(), Window.GetHeight<uint32_t>()});
        ViewportState.setScissors(ViewportRect);
        ViewportState.setScissorCount(1);
        const vk::Viewport Viewport = GetViewport();
        ViewportState.setViewports(Viewport);

        vk::ShaderModuleCreateInfo VertexShaderModuleInfo{};
        //VertexShaderModuleInfo.setCode();

        vk::PipelineShaderStageCreateInfo ShaderStageCreateInfo{};
        ShaderStageCreateInfo.setStage(vk::ShaderStageFlagBits::eVertex);
        //ShaderStageCreateInfo.setModule()
        
        vk::GraphicsPipelineCreateInfo CreateInfo{};
        CreateInfo.setPColorBlendState(&ColorBlendState);
        CreateInfo.setPVertexInputState(&VertexInputState);
        CreateInfo.setPRasterizationState(&RasterizationState);
        CreateInfo.setPViewportState(&ViewportState);
        CreateInfo.setRenderPass(m_RenderPass);
        CreateInfo.setStages(ShaderStageCreateInfo);

        m_GraphicsPipeline = m_Device.createGraphicsPipeline(nullptr, CreateInfo).value;
        if(!m_GraphicsPipeline)
        {
            HYDRO_VULKAN_ERROR("Failed to create Graphics Pipeline!");
            return false;
        }
        return true;
    }

    bool VulkanRendererBackend::CreateCommandPool()
    {
        if(!m_GraphicsQueueIndex.has_value()) return false;
        vk::CommandPoolCreateInfo CreateInfo{};
        CreateInfo.setQueueFamilyIndex(m_GraphicsQueueIndex.value());
        
        m_CommandPool = m_Device.createCommandPool(CreateInfo);
        if(!m_CommandPool)
        {
            HYDRO_VULKAN_ERROR("Failed to create command pool!");
            return false;
        }

        HYDRO_VULKAN_SUCCESS("Successfully created command pool");
        return true;
    }

    bool VulkanRendererBackend::CreateRenderPass()
    {
        vk::AttachmentDescription AttachmentDescription{};
        AttachmentDescription.setLoadOp(vk::AttachmentLoadOp::eClear);
        AttachmentDescription.setInitialLayout(vk::ImageLayout::eUndefined);
        AttachmentDescription.setFinalLayout(vk::ImageLayout::ePresentSrcKHR);
        AttachmentDescription.setStoreOp(vk::AttachmentStoreOp::eStore);
        AttachmentDescription.setSamples(vk::SampleCountFlagBits::e1);
        AttachmentDescription.setFormat(m_Format);
        
        vk::AttachmentReference AttachmentReference{};
        AttachmentReference.setAttachment(0);
        AttachmentReference.setLayout(vk::ImageLayout::eColorAttachmentOptimal);
        
        vk::SubpassDescription SubpassDescription{};
        SubpassDescription.setColorAttachments(AttachmentReference);
        SubpassDescription.setColorAttachmentCount(1);
        SubpassDescription.setInputAttachmentCount(0);
        SubpassDescription.setPreserveAttachmentCount(0);
        SubpassDescription.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);
        
        vk::RenderPassCreateInfo CreateInfo{};
        CreateInfo.setAttachments(AttachmentDescription);
        CreateInfo.setAttachmentCount(1);
        CreateInfo.setSubpasses(SubpassDescription);
        CreateInfo.setSubpassCount(1);
        

        m_RenderPass = m_Device.createRenderPass(CreateInfo);
        if(!m_RenderPass)
        {
            HYDRO_VULKAN_ERROR("Failed to create Render Pass!");
            return false;
        }
        return true;
    }

    bool VulkanRendererBackend::CreateFramebuffers()
    {
        const Window& Window = m_Application.GetWindow();
        vk::FramebufferCreateInfo CreateInfo{};
        CreateInfo.setRenderPass(m_RenderPass);
        CreateInfo.setWidth(Window.GetWidth<uint32_t>());
        CreateInfo.setHeight(Window.GetHeight<uint32_t>());
        CreateInfo.setLayers(1);
        CreateInfo.setAttachmentCount(1);

        m_Framebuffers.resize(m_ImageCount);
        for(size_t i = 0; i < m_ImageCount; i++)
        {
            CreateInfo.setAttachments(m_SwapchainImagesViews[i]);
            m_Framebuffers[i] = m_Device.createFramebuffer(CreateInfo);
            if(!m_Framebuffers[i])
            {
                HYDRO_VULKAN_ERROR("Failed to create a framebuffer for image {}", i);
                return false;
            }
        }

        HYDRO_VULKAN_SUCCESS("Successfully create {} framebuffers!", m_ImageCount);
        return true;
    }

    vk::Viewport VulkanRendererBackend::GetViewport() const
    {
        const Window& Window = m_Application.GetWindow();
        vk::Viewport Viewport{};
        Viewport.setX(0); Viewport.setY(0);
        Viewport.setWidth(Window.GetWidth());
        Viewport.setHeight(Window.GetHeight());
        Viewport.setMinDepth(0.0f);
        Viewport.setMaxDepth(1.0f);
        return Viewport;
    }

    std::string VulkanRendererBackend::GetGPUTypeString(const vk::PhysicalDeviceType& DeviceType) const
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

    vk::CullModeFlags VulkanRendererBackend::ConvertCullMode(CullMode Mode)
    {
        switch (Mode)
        {
        case CullMode::FrontFace:
            return vk::CullModeFlagBits::eFront;
        case CullMode::BackFace:
            return vk::CullModeFlagBits::eBack;
        case CullMode::FrontAndBackFaces:
            return vk::CullModeFlagBits::eFrontAndBack;
        case CullMode::None:
            return vk::CullModeFlagBits::eNone;
        }
        return vk::CullModeFlagBits::eNone;
    }

    uint32_t VulkanRendererBackend::GetNextSwapchainImage() const
    {
        const uint32_t NextImage = m_Device.acquireNextImageKHR(m_Swapchain, 0, m_AcquireImageSemaphore, nullptr).value;
        return NextImage;
    }
}
