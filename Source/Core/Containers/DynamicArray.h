#pragma once
#include "Core/Iterator.h"
#include "Core/Assertion.h"
#include "Core/Memory.h"
#include "Math/Functions.h"
#include "Function.h"

#include <initializer_list>
#include <algorithm>




namespace Hydro
{
    template<typename T>
    class Array final : public Iterable<T>
    {
    public:
        using ValueType = T;
        using PointerType = T*;
        using ConstPointerType = const T*;
        using ReferenceType = T&;
        using ConstReferenceType = const T&;
        using SizeType = size_t;
        using ForwardType = T&&;
        using Iterator = Iterator<T>;
        using ConstIterator = ConstIterator<T>;
        using Predicate = Function<bool(ConstReferenceType)>;
        template<typename Out>
        using Selector = Function<Out*(ReferenceType)>;
        
        Array()
        {
            m_Allocated = 1;
            m_Data = Memory::Calloc<T>(m_Allocated);
            m_Count = 0;
        }

        Array(SizeType Count)
        {
            m_Allocated = Math::NearestPowerOfTwo<SizeType>(Count);
            m_Data = Memory::Calloc<T>(m_Allocated);
            m_Count = 0;
        }

        Array(const std::initializer_list<T>& List) : m_Count(List.size()), m_Allocated(List.size())
        {
            m_Data = Memory::Calloc<T>(m_Allocated);
            std::copy(List.begin(), List.end(), m_Data);
        }
        
        Array(ConstPointerType Data, SizeType Count) : m_Count(Count), m_Allocated(Count)
        {
            m_Data = Memory::Calloc<T>(m_Allocated);
            std::copy(Data, Data + Count, m_Data);
        }

        Array(const Array& Other) : m_Count(Other.m_Count), m_Allocated(Other.m_Allocated)
        {
            m_Data = Memory::Calloc<T>(m_Allocated);
            std::copy(Other.begin(), Other.end(), m_Data);
        }

        Array(Array&& Other) noexcept
        {
            m_Data = Other.m_Data;
            m_Count = Other.m_Count;
            m_Allocated = Other.m_Allocated;

            Other.m_Data = nullptr;
            Other.m_Count = 0;
            Other.m_Allocated = 0;
        }

        ~Array() override
        {
            Memory::Free(m_Data);
        }

        Array& operator=(const Array& Other)
        {
            if(this == &Other)
                return *this;

            m_Allocated = Other.m_Allocated;
            m_Count = Other.m_Count;
            Memory::Free(m_Data);
            m_Data = Memory::Calloc<T>(m_Allocated);
            std::copy(Other.begin(), Other.end(), m_Data);
            return *this;
        }

        Array& operator=(Array&& Other) noexcept
        {
            if(this == &Other)
                return *this;
            
            m_Data = Other.m_Data;
            m_Count = Other.m_Count;
            m_Allocated = Other.m_Allocated;

            Other.m_Data = nullptr;
            Other.m_Count = 0;
            Other.m_Allocated = 0;
            return *this;
        }

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

        ReferenceType First()
        {
            HYDRO_ASSERT(m_Count != 0, "Cannot get first element, array is empty!");
            return m_Data[0];
        }
        
        ConstReferenceType First() const
        {
            HYDRO_ASSERT(m_Count != 0, "Cannot get first element, array is empty!");
            return m_Data[0];
        }

        ReferenceType Last()
        {
            HYDRO_ASSERT(m_Count != 0, "Cannot get last element, array is empty!");
            return m_Data[m_Count - 1];
        }
        
        ConstReferenceType Last() const
        {
            HYDRO_ASSERT(m_Count != 0, "Cannot get first element, array is empty!");
            return m_Data[m_Count - 1];
        }

        void Add(ConstReferenceType Element)
        {
            if(m_Count >= m_Allocated)
            {
                m_Allocated = Realloc(m_Allocated);
                PointerType Realloc = Memory::Calloc<T>(m_Allocated);
                for(SizeType i = 0; i < m_Count; ++i)
                    Realloc[i] = m_Data[i];
                Memory::Free(m_Data);
                m_Data = Realloc;
            }
            
            m_Data[m_Count++] = Element;
        }

        void AddRange(const std::initializer_list<T>& List)
        {
            if(m_Count + List.size() >= m_Allocated)
            {
                m_Allocated = Realloc(m_Allocated);
                PointerType Realloc = Memory::Calloc<T>(m_Allocated);
                for(SizeType i = 0; i < m_Count; ++i)
                    Realloc[i] = m_Data[i];
                Memory::Free(m_Data);
                m_Data = Realloc;
            }
            
            std::copy(List.begin(), List.end(), &m_Data[m_Count]);
            m_Count += List.size();
        }

        void AddRange(ConstPointerType Data, SizeType Count)
        {
            if(m_Count + Count >= m_Allocated)
            {
                m_Allocated = Realloc(m_Allocated);
                PointerType Realloc = Memory::Calloc<T>(m_Allocated);
                for(SizeType i = 0; i < m_Count; ++i)
                    Realloc[i] = m_Data[i];
                Memory::Free(m_Data);
                m_Data = Realloc;
            }
            
            std::copy(Data, Data + Count, &m_Data[m_Count]);
            m_Count += Count;
        }

        bool Remove(ConstReferenceType Element)
        {
            SizeType Index = Find(Element);
            if(Index == -1) return false;

            std::move(m_Data + Index + 1, m_Data + m_Count, m_Data + Index);
            m_Count--;
            return true;
        }

        void RemoveAt(SizeType Index)
        {
            HYDRO_ASSERT(Index < m_Count, "Index out of bounds!");
            std::move(m_Data + Index + 1, m_Data + m_Count, m_Data + Index);
            m_Count--;
        }

        bool RemoveAll(ConstReferenceType Element)
        {
            SizeType Index;
            bool Found = false;
            while ((Index = Find(Element)) != -1)
            {
                if(Index < m_Count) std::move(m_Data + Index + 1, m_Data + m_Count, m_Data + Index);
                m_Count--;
                Found = true;
            }
            return Found;
        }

        bool Contains(ConstReferenceType Element) const
        {
            for(SizeType i = 0; i < m_Count; ++i)
                if(m_Data[i] == Element)
                    return true;
            return false;
        }

        SizeType Find(ConstReferenceType Element) const
        {
            for(SizeType i = 0; i < m_Count; ++i)
                if(m_Data[i] == Element)
                    return i;
            return -1;
        }

        void Pop()
        {
            RemoveAt(m_Count);
        }
        
        void Clear()
        {
            m_Count = 0;
        }

        // Return an array of pointer to elements of type T, inside m_Data, where each element satisfy Predicate
        Array<T*> Where(const Predicate& Predicate) const
        {
            if(!Predicate) return {};
            Array<T*> Result;
            for(SizeType i = 0; i < m_Count; ++i)
            {
                if(Predicate(m_Data[i]))
                    Result.Add(&m_Data[i]);
            }
            return Result;
        }

        // Return a pointer to first elements of type T, inside m_Data, which satisfy Predicate
        T* Single(const Predicate& Predicate) const
        {
            if(!Predicate) return nullptr;
            for(SizeType i = 0; i < m_Count; ++i)
            {
                if(Predicate(m_Data[i]))
                    return &m_Data[i];
            }
            return nullptr;
        }

        template<typename Out>
        Array<Out*> Select(const Selector<Out>& Selector) const
        {
            if(!Selector) return {};
            Array<Out*> Result;
            for(SizeType i = 0; i < m_Count; ++i)
            {
                Result.Add(Selector(m_Data[i]));
            }
            return Result;
        }

        bool IsEmpty() const { return m_Count == 0; }
        
        Iterator begin() override { return m_Data; }
        Iterator end() override { return m_Data + m_Count; }
        
        ConstIterator begin() const override{ return m_Data; }
        ConstIterator end() const override { return (PointerType)(&m_Data[0] + m_Count); }

        ConstPointerType Data() const { return m_Data; }
        PointerType Data() { return m_Data; }

        SizeType Count() const { return m_Count; }

        bool operator==(const Array& Other) const
        {
            if(m_Count != Other.m_Count) return false;
            for(SizeType i = 0; i < m_Count; ++i)
                if(m_Data[i] != Other.m_Data[i]) return false;
            return true;
        }
    private:
        PointerType m_Data = nullptr;
        SizeType m_Count = 0;
        SizeType m_Allocated = 0;

        size_t Realloc(const size_t Current) const
        {
            return Current * 2;
        }
    };
}
