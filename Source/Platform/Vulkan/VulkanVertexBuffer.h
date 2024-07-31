#pragma once
#include "Core/VertexBuffer.h"

namespace Hydro
{
   class VulkanVertexBuffer : public VertexBuffer
   {
   public:
      VulkanVertexBuffer(Vertex* Data, size_t Count) : VertexBuffer(Data, Count){}
      
      void SendData() override;
      void Bind() const override;
      void Unbind() const override;
   };
}
