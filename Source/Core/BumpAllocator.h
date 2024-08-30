#pragma once
#include "Containers/StaticArray.h"
#include "Assertion.h"
#include "Macros.h"
#include <functional>

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
        static constexpr uint32_t UninitializedValue = HYDRO_UNINITIALIZED;

        BumpAllocator()
        {
            m_Data.Memset(0, Size, UninitializedValue);
        }

        template<typename... Args>
        PointerType New(Args&&... Arguments)
        {
            for(SizeType i = 0; i < Size; ++i)
            {
                const uint8_t* Data = (uint8_t*)&m_Data[i];
                for(size_t Byte = 0; Byte < sizeof(T); ++Byte)
                {
                    if(Data[Byte] == 0xCDui8)
                        return nullptr;
                }
                
                m_Data[i] = std::move(T(std::forward<Args>(Arguments)...));
                return &m_Data[i];
            }
            return nullptr;
        }

        void Free(PointerType Ptr)
        {
            if(!Ptr) return;
            HYDRO_ASSERT(Ptr >= &m_Data[0] && Ptr < &m_Data[0] + Size, "Memory is not allocated from this bump allocator!");
            SizeType Index = Ptr - &m_Data[0];
            Ptr->~T();
            m_Data.Memset(Index, Index + 1, UninitializedValue);
        }

        SizeType Count() const
        {
            SizeType Result = 0;
            for(SizeType i = 0; i < Size; ++i)
            {
                const uint8_t* Data = (uint8_t*)&m_Data[i];
                for(size_t Byte = 0; Byte < sizeof(T); ++Byte)
                {
                    if(Data[Byte] == 0xCDui8)
                        return -1;
                }
                
                ++Result;
            }
            return Result;
        }

        void ForEachValid(const std::function<void(T* Element)>& Func)
        {
            for(SizeType i = 0; i < Size; ++i)
            {
                const uint8_t* Data = (uint8_t*)&m_Data[i];
                
                for(size_t Byte = 0; Byte < sizeof(T); ++Byte)
                {
                    if(Data[Byte] == 0xCDui8)
                        continue;
                }
                
                Func(&m_Data[i]);
            }
        }

        T* Single(const std::function<bool(T* Element)>& Predicate)
        {
            ForEachValid([&Predicate](T* Element)
            {
                if(Predicate(Element))
                {
                    return Element;
                }
            });
            return nullptr;
        }

        
    private:
         ArrayType m_Data;
    };
}
