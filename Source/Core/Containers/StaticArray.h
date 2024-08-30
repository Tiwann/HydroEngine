#pragma once
#include "Core/Iterator.h"
#include "Core/Assertion.h"
#include <initializer_list>
#include <algorithm>
#include <cstring>

namespace Hydro
{
    template<typename T, size_t N>
    class StaticArray : public Iterable<T>
    {
    public:
        using ValueType = T;
        using PointerType = T*;
        using ConstPointerType = const T*;
        using ReferenceType = T&;
        using ConstReferenceType = const T&;
        using SizeType = size_t;
        
        StaticArray()
        {
            std::memset(m_Data, 0, N * sizeof(T));
        }

        StaticArray(const std::initializer_list<T>& List)
        {
            std::copy(List.begin(), List.end(), m_Data);
        }
        
        StaticArray(ConstPointerType Data, SizeType Count)
        {
            HYDRO_ASSERT(Count <= N, "Cannot fill in an Array<N> with more elements than N");
            std::copy(Data, Data + Count, m_Data);
        }

        StaticArray(const StaticArray& Other)
        {
            std::copy(Other.begin(), Other.end(), m_Data);
        }

        StaticArray(StaticArray&& Other) noexcept = delete;

        StaticArray& operator=(const StaticArray& Other)
        {
            if(this == &Other)
                return *this;
            
            std::copy(Other.begin(), Other.end(), m_Data);
            return *this;
        }

        StaticArray& operator=(StaticArray&& Other) noexcept = delete;

        ReferenceType operator[](SizeType Index)
        {
            HYDRO_ASSERT(Index <= N, "Index out of bounds");
            return m_Data[Index];
        }

        ConstReferenceType operator[](SizeType Index) const
        {
            HYDRO_ASSERT(Index <= N, "Index out of bounds");
            return m_Data[Index];
        }

        void SetAt(SizeType Index, ConstReferenceType Element)
        {
            HYDRO_ASSERT(Index <= N, "Index out of bounds");
            m_Data[Index] = Element;
        }

        ReferenceType GetAt(SizeType Index)
        {
            HYDRO_ASSERT(Index <= N, "Index out of bounds");
            return m_Data[Index];
        }

        ConstReferenceType GetAt(SizeType Index) const
        {
            HYDRO_ASSERT(Index <= N, "Index out of bounds");
            return m_Data[Index];
        }

        
        bool Contains(ConstReferenceType Element)
        {
            for(SizeType i = 0; i < N; ++i)
                if(m_Data[i] == Element)
                    return true;
            return false;
        }

        SizeType Find(ConstReferenceType Element)
        {
            for(SizeType i = 0; i < N; ++i)
                if(m_Data[i] == Element)
                    return i;
            return -1;
        }

        void Fill(const T& Value)
        {
            for(SizeType i = 0; i < N; ++i)
                m_Data[i] = Value;
        }

        void Memset(SizeType Begin, SizeType End, uint32_t Value)
        {
            HYDRO_ASSERT(Begin < End, "Index out of bounds!");
            HYDRO_ASSERT(End <= N, "index out of bounds!");
            
            std::memset(m_Data + Begin, Value, (End - Begin) * sizeof(T));
        }
        
        Iterator<T> begin() override { return m_Data; }
        Iterator<T> end() override { return m_Data + N; }
        
        ConstIterator<T> begin() const override{ return m_Data; }
        ConstIterator<T> end() const override { return (PointerType)(&m_Data[0] + N); }

        ConstPointerType Data() const { return m_Data; }
        PointerType Data() { return m_Data; }

        constexpr SizeType Count() const { return N; }

        operator PointerType() { return m_Data; }
        operator ConstPointerType() const { return m_Data; }
    private:
        ValueType m_Data[N];
    };
}
