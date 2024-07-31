#include "HydroPCH.h"
#include "VulkanTexture2D.h"

#include "VulkanRendererBackend.h"
#include "Core/Application.h"
#include "Core/Memory.h"

namespace Hydro
{
    VulkanTexture2D::VulkanTexture2D(const std::string& Name, uint32_t Slot) : Texture2D(Name, Slot)
    {
        m_RendererBackend = Cast<VulkanRendererBackend>(Application::GetCurrentApplication().GetRendererBackend());
        if(!m_RendererBackend)
        {
            HYDRO_LOG(Texture2D, Error, "Failed to create Texture2D: No Renderer Backend found.");
            return;
        }
    }

    void VulkanTexture2D::SetImage(const Ref<Image>& Image)
    {
        vk::ImageCreateInfo CreateInfo{};
        CreateInfo.setFormat(vk::Format::eR8G8B8A8Unorm);
        CreateInfo.setExtent({Image->GetWidth(), Image->GetHeight(), 1});
        CreateInfo.setMipLevels(1);
        CreateInfo.setSamples(vk::SampleCountFlagBits::e1);
        CreateInfo.setUsage(vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled);
        CreateInfo.setInitialLayout(vk::ImageLayout::eUndefined);
        CreateInfo.setImageType(vk::ImageType::e2D);
        const uint32_t QueueIndices[] { m_RendererBackend->GetGraphicsQueueFamilyIndex() };
        CreateInfo.setQueueFamilyIndices(QueueIndices);
        CreateInfo.setArrayLayers(1);

        m_Image = m_RendererBackend->CreateImage(CreateInfo);
        if(!m_Image)
        {
            HYDRO_LOG(Texture2D, Error, "Failed to set Texture2D image! Please refer to vulkan debug messenger.");
            return;
        }

        const auto Requirements = m_RendererBackend->GetDevice().getImageMemoryRequirements(m_Image);
        vk::MemoryAllocateInfo AllocateInfo{};
        AllocateInfo.setAllocationSize(Image->GetSize());
        
        
        const auto PhysicalDeviceMemoryProperties = m_RendererBackend->GetPhysicalDevice().getMemoryProperties2();
        for(uint32_t i{0}; i < PhysicalDeviceMemoryProperties.memoryProperties.memoryTypeCount; i++)
        {
            if(Requirements.memoryTypeBits & (1 << i)
                && (PhysicalDeviceMemoryProperties.memoryProperties.memoryTypes[i].propertyFlags & (vk::MemoryPropertyFlagBits::eDeviceLocal | vk::MemoryPropertyFlagBits::eHostVisible)))
            {
                AllocateInfo.setMemoryTypeIndex(i);
                break;
            }
        }
 
        m_Memory = m_RendererBackend->AllocateMemory(AllocateInfo);
        m_RendererBackend->GetDevice().bindImageMemory(m_Image, m_Memory, 0);
        Width = Image->GetWidth();
        Height = Image->GetHeight();
    }

    Ref<Image> VulkanTexture2D::GetImage() const
    {
        if(!m_Image) return nullptr;
        if(!m_Memory) return nullptr;

        const uint64_t Size = Width * Height * 4;
        void* MappedMemory = m_RendererBackend->GetDevice().mapMemory(m_Memory, 0, Size);
        const Buffer ImageBuffer((uint8_t*)MappedMemory, Size);
        Ref<Image> Image = Image::Create(ImageBuffer, RGBA8);
        m_RendererBackend->GetDevice().unmapMemory(m_Memory);
        return Image;
    }

    void VulkanTexture2D::Bind() const
    {
    }
}
