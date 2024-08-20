#include "HydroPCH.h"
#include "VertexBuffer.h"

#include "Macros.h"
#include "Platform/PlatformVertexBuffer.h"

namespace Hydro
{
    VertexBuffer::VertexBuffer() : m_Data(nullptr, 0)
    {
    }

    VertexBuffer::VertexBuffer(Vertex* Data, size_t Count) : m_Data(Data, Count)
    {
    }

    Ref<VertexBuffer> VertexBuffer::Create()
    {
        HYDRO_RHI_PLATFORM_RETURN(VertexBuffer);
    }

    Ref<VertexBuffer> VertexBuffer::Create(Vertex* Data, size_t Count)
    {
        HYDRO_RHI_PLATFORM_RETURN(VertexBuffer, Data, Count);
    }

    void VertexBuffer::SendData(Vertex* Data, size_t Count)
    {
        m_Data = BufferView(Data, Count);
    }
}
