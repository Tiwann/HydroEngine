#include "HydroPCH.h"
#include "IndexBuffer.h"
#include "Macros.h"
#include "Platform/PlatformIndexBuffer.h"

namespace Hydro
{
    IndexBuffer::IndexBuffer(uint32_t* Indices, size_t Count) :
    m_Data(Indices, Count)
    {
    }

    size_t IndexBuffer::Count() const
    {
        return m_Data.Count();
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* Indices, size_t Count)
    {
        HYDRO_RHI_PLATFORM_RETURN(IndexBuffer, Indices, Count);
    }
}
