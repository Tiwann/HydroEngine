#pragma once
#include "Core/Texture2D.h"


namespace Hydro
{
    class VulkanRendererBackend;
    
    class VulkanTexture2D : public Texture2D
    {
    public:
        VulkanTexture2D(const std::string& Name, u32 Slot);
        void SetData(const Ref<Image>& Image) override;
        Ref<Image> GetImage() const override;
        void Bind() const override;
    private:
        Ref<VulkanRendererBackend> m_RendererBackend;
        u32 Width, Height;
        vk::Image m_Image;
        vk::DeviceMemory m_Memory;
    };
}
