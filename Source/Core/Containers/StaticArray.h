#pragma once
#include "Core/Iterator.h"
#include "Core/Assertion.h"

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
            for(SizeType i = 0; i < N; ++i)
            {
                m_Data[i] = T();
            }
        }

        StaticArray(const std::initializer_list<T>& List) : m_Count(List.size())
        {
            std::copy(List.begin(), List.end(), m_Data);
        }
        
        StaticArray(ConstPointerType Data, SizeType Count) : m_Count(Count)
        {
            HYDRO_ASSERT(Count <= N, "Cannot fill in an Array<N> with more elements than N");
            std::copy(Data, Data + Count, m_Data);
        }

        StaticArray(const StaticArray& Other) : m_Count(Other.m_Count)
        {
            std::copy(Other.begin(), Other.end(), m_Data);
        }

        StaticArray(StaticArray&& Other) noexcept = delete;

        StaticArray& operator=(const StaticArray& Other)
        {
            if(this == &Other)
                return *this;
            
            std::copy(Other.begin(), Other.end(), m_Data);
            m_Count = Other.m_Count;
            return *this;
        }

        StaticArray& operator=(StaticArray&& Other) noexcept = delete;

        ReferenceType operator[](SizeType Index)
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            return m_Data[Index];
        }

        ConstReferenceType operator[](SizeType Index) const
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            return m_Data[Index];
        }

        void SetAt(SizeType Index, ConstReferenceType Element)
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            m_Data[Index] = Element;
        }

        ReferenceType GetAt(SizeType Index)
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            return m_Data[Index];
        }

        ConstReferenceType GetAt(SizeType Index) const
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            return m_Data[Index];
        }

        void Add(ConstReferenceType Element)
        {
            HYDRO_ASSERT(m_Count < N, "Array is full");
            m_Data[m_Count] = Element;
            m_Count++;
        }

        void AddRange(const std::initializer_list<T>& List)
        {
            HYDRO_ASSERT(m_Count + List.size() < N, "Cannot add that much element to array. Not enough size");
            std::copy(List.begin(), List.end(), &m_Data[m_Count]);
            m_Count += List.size();
        }

        void AddRange(ConstPointerType Data, SizeType Count)
        {
            HYDRO_ASSERT(m_Count + Count < N, "Cannot add that much element to array. Not enough size");
            std::copy(Data, Data + Count, &m_Data[m_Count]);
            m_Count += Count;
        }

        bool Contains(ConstReferenceType Element)
        {
            for(SizeType i = 0; i < m_Count; ++i)
                if(m_Data[i] == Element)
                    return true;
            return false;
        }

        SizeType Find(ConstReferenceType Element)
        {
            for(SizeType i = 0; i < m_Count; ++i)
                if(m_Data[i] == Element)
                    return i;
            return -1;
        }
        
        Iterator<T> begin() override { return m_Data; }
        Iterator<T> end() override { return m_Data + m_Count; }
        
        ConstIterator<T> begin() const override{ return m_Data; }
        ConstIterator<T> end() const override { return (PointerType)(&m_Data[0] + m_Count); }

        ConstPointerType Data() const { return m_Data; }
        PointerType Data() { return m_Data; }

        SizeType Count() const { return m_Count; }
    private:
        ValueType m_Data[N];
        SizeType m_Count = 0;
        
    };
}
