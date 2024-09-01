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
            m_AvailableFlags.Fill(true);
            m_Data.Fill(T());
        }

        ~BumpAllocator()
        {
            for (const Array<T*> All = GetAllValid(); T* Element : All)
            {
                Free(Element);
            }
            m_AvailableFlags.Fill(false);
        }
        
        PointerType New()
        {
            for(SizeType i = 0; i < Size; ++i)
            {
                if(!m_AvailableFlags[i])
                    continue;
                
                m_AvailableFlags[i] = false;
                ++m_Count;
                return &m_Data[i];
            }
            return nullptr;
        }

        void Free(PointerType Ptr)
        {
            if(!Ptr) return;
            HYDRO_ASSERT(Ptr >= &m_Data[0] && Ptr < &m_Data[0] + Size, "Memory is not allocated from this bump allocator!");
            SizeType Index = Ptr - &m_Data[0];
            m_AvailableFlags[Index] = true;
            --m_Count;
        }

        SizeType Count() const
        {
            return m_Count;
        }

        Array<T*> GetAllValid()
        {
            Array<T*> Result;
            for(SizeType i = 0; i < Size; ++i)
            {
                if(!m_AvailableFlags[i])
                    Result.Add(&m_Data[i]);
            }
            return Result;
        }

        T* Single(const std::function<bool(const T*)>& Predicate)
        {
            for(SizeType i = 0; i < Size; ++i)
            {
                if(!m_AvailableFlags[i])
                {
                    if(Predicate(&m_Data[i]))
                        return &m_Data[i];
                }
            }
            return nullptr;
        }

        Array<T*> Where(const std::function<bool(const T*)>& Predicate)
        {
            Array<T*> Result;
            for(SizeType i = 0; i < Size; ++i)
            {
                if(!m_AvailableFlags[i] && Predicate(&m_Data[i]))
                    Result.Add(&m_Data[i]);
            }
            return Result;
        }
    
    private:
        StaticArray<bool, Size> m_AvailableFlags;
        ArrayType m_Data;
        SizeType m_Count = 0;
    };
}
