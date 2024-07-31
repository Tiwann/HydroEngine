#pragma once
#include "Core/VertexArray.h"

namespace Hydro
{
    class VulkanVertexArray : public VertexArray
    {
    public:
        VulkanVertexArray() : VertexArray(){}
        void Bind() const override;
        void Unbind() const override;
        void SetBufferLayout() override;
    };
}
