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

    Ref<IndexBuffer> IndexBuffer::Create(const std::initializer_list<uint32_t>& List)
    {
        uint32_t* Data = const_cast<uint32_t*>(List.begin());
        size_t Size = List.size();
        HYDRO_RHI_PLATFORM_RETURN(IndexBuffer, Data, Size);
    }
}
