#pragma once
#include "Containers/StaticArray.h"
#include "Assertion.h"

namespace Hydro
{
    template<typename T, size_t Size>
    class BumpAllocator
    {
    public:
        using ArrayType = StaticArray<T, Size>;
        using SizeType = typename ArrayType::SizeType;
        using ValueType = typename ArrayType::ValueType;
        using PointerType = typename ArrayType::PointerType;
        using ConstPointerType = typename ArrayType::ConstPointerType;
        using ReferenceType = typename ArrayType::ReferenceType;
        using ConstReferenceType = typename ArrayType::ConstReferenceType;
        static constexpr uint32_t UninitializedValue = 0xFFFFFFFF;

        BumpAllocator()
        {
            m_Data.Memset(0, Size, UninitializedValue);
        }

        template<typename... Args>
        PointerType New(Args&&... Arguments)
        {
            for(SizeType i = 0; i < Size; ++i)
            {
                if(memcmp(m_Data.Data() + i, &UninitializedValue, sizeof(int)) != 0)
                    continue;
                m_Data[i] = T(std::forward<Args>(Arguments)...);
                return &m_Data[i];
            }
            return nullptr;
        }

        void Free(PointerType Ptr)
        {
            HYDRO_ASSERT(Ptr >= &m_Data[0] && Ptr < &m_Data[0] + Size, "Memory is not allocated from this bump allocator!");
            SizeType Index = Ptr - &m_Data[0];
            m_Data.Memset(Index, Index + 1, UninitializedValue);
        }

        
    private:
         ArrayType m_Data;
    };
}
