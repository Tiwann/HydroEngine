#pragma once
#include "Core/IndexBuffer.h"


namespace Hydro
{
    class VulkanIndexBuffer : public IndexBuffer
    {
    public:
        VulkanIndexBuffer(uint32_t* Indices, size_t Count) : IndexBuffer(Indices, Count)
        {
        }

        void Bind() override;
        void Unbind() override;
        void SendData() override;
    };
}
