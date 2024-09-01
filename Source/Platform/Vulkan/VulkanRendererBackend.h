#pragma once
#include "Core/RendererBackend.h"
#include "Core/LogCategory.h"
#include <optional>

HYDRO_DECLARE_LOG_CATEGORY_STATIC(Vulkan, "VULKAN");

#define VK_FAILED(Res) (((vk::Result)(Res)) != vk::Result::eSuccess)

#define HYDRO_CHECK_VK_RESULT(Result, Message) \
    if(VK_FAILED(Result)) \
    { \
        HYDRO_LOG(Vulkan, Error, Message); \
        return false; \
    } ((void)0)


namespace Hydro
{
    class VulkanRendererBackend : public RendererBackend
    {
    public:
        
        VulkanRendererBackend(Application* Owner);
        ~VulkanRendererBackend() override;


        bool Initialize() override;
        void Destroy() override;
        void ClearDepthBuffer() override;
        void ClearColorBuffer(const Color& color) override;
        void SwapBuffers() override;

        vk::Image CreateImage(const vk::ImageCreateInfo& CreateInfo);
        vk::DeviceMemory AllocateMemory(const vk::MemoryAllocateInfo& AllocateInfo);
        void FreeMemory(const vk::DeviceMemory& Memory) const;
        vk::Device GetDevice() const;
        vk::Instance GetInstance() const;
        vk::PhysicalDevice GetPhysicalDevice() const;
        vk::Queue GetGraphicsQueue() const;
        uint32 GetImageCount() const;
        uint32 GetGraphicsQueueFamilyIndex() const;

        void DrawIndexed(DrawMode Mode, const Vao& VAO, const Vbo& VBO, const Ibo& IBO, const Ref<Shader>& Shader) override;
        void SetCullMode(CullMode Mode) override;
        

    private:
        vk::Instance             m_Instance{nullptr};
        vk::PhysicalDevice       m_PhysicalDevice{nullptr};
        vk::SurfaceKHR           m_Surface{nullptr};
        vk::Device               m_Device{nullptr};
        vk::Queue                m_GraphicsQueue{nullptr};
        vk::Queue                m_PresentQueue{nullptr};
        vk::Semaphore            m_AcquireImageSemaphore{nullptr};
        vk::Semaphore            m_SubmitSemaphore{nullptr};
        vk::Semaphore            m_PresentSemaphore{nullptr};
        vk::CommandPool          m_CommandPool{nullptr};
        vk::RenderPass           m_RenderPass{nullptr};
        vk::Pipeline             m_GraphicsPipeline{nullptr};
        std::vector<vk::Framebuffer> m_Framebuffers;
        std::vector<const char*> m_InstanceExtensions{};
        std::vector<const char*> m_DeviceExtensions{};
        std::vector<const char*> m_Layers{};
        std::optional<uint32>  m_GraphicsQueueIndex;
        std::optional<uint32>  m_PresentQueueIndex;
        vk::PresentModeKHR       m_PresentMode{vk::PresentModeKHR::eFifo};
        vk::Format               m_Format{vk::Format::eUndefined};
        vk::SwapchainKHR         m_Swapchain{nullptr};
        std::vector<vk::Image>   m_SwapchainImages;
        std::vector<vk::ImageView> m_SwapchainImagesViews;

        std::vector<vk::Image> m_TextureImages;
        std::vector<vk::DeviceMemory> m_Memories;
        uint32 m_ImageCount;
#if defined(HYDRO_DEBUG)
        vk::DebugUtilsMessengerEXT m_DebugMessenger;
#endif

    private:
        bool CreateInstance();
        bool SelectPhysicalDevice();
        bool CreateWindowSurface();
        bool CreateDevice();
        bool CreateSwapchain();
        bool CreateSemaphores();
        bool CreateGraphicsPipeline();
        bool CreateCommandPool();
        bool CreateRenderPass();
        bool CreateFramebuffers();
        vk::Viewport GetViewport() const;
        std::string GetGPUTypeString(const vk::PhysicalDeviceType& DeviceType) const;
        vk::CullModeFlags ConvertCullMode(CullMode Mode);
        uint32 GetNextSwapchainImage() const;
    public:
        

    protected:
        using Super = RendererBackend;
    };
}
