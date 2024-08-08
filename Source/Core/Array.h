#pragma once
#include "Buffer.h"
#include "Iterator.h"
#include "Log.h"
#include "LogCategory.h"
#include "LogVerbosity.h"
#include "Memory.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(DynamicArray, "DYNAMIC ARRAY")

namespace Hydro
{

    
    template<typename T>
    class Array : public Iterable<T>
    {
    public:
        using SizeType = size_t;
        using ElementType = T;
        using PointerType = ElementType*;
        using ConstPointerType = ElementType const*;
        using RefType = ElementType&;
        using ConstRefType = ElementType const&;
        using Iterator = Iterator<ElementType>;
        using ConstIterator = ConstIterator<ElementType>;
        
        Array() : m_Allocated(1)
        {
            m_Data = (PointerType)malloc(sizeof(ElementType));
            std::memset(m_Data, 0, sizeof(ElementType));
        }

        Array(SizeType Count) : m_Allocated(Count)
        {
            m_Data = (PointerType)malloc(m_Allocated * sizeof(ElementType));
        }
        
        Array(const std::initializer_list<ElementType>& List) : m_Allocated(List.size())
        {
            m_Data = (PointerType)malloc(m_Allocated * sizeof(ElementType));
            for(const auto& Elem : List)
            {
                Add(Elem);
            }
        }

        Array(const Array& other) : Iterable<T>(other),
        m_Allocated(other.m_Allocated),
        m_Count(other.m_Count)
        {
            if(m_Data) free(m_Data);
            m_Data = (PointerType)malloc(other.m_Allocated);
            std::copy(other.begin(), other.end(), m_Data);
        }

        Array(Array&& other) noexcept
            : Iterable<T>(std::move(other)),
              m_Allocated(other.m_Allocated),
              m_Count(other.m_Count)
        {
            m_Data = (PointerType)malloc(other.m_Allocated);
            std::move(other.begin(), other.end(), m_Data);
            free(other.m_data);
        }

        Array& operator=(const Array& other)
        {
            if (this == &other)
                return *this;
            if(m_Data) free(m_Data);
            m_Data = (PointerType)malloc(other.m_Allocated);
            std::copy(other.begin(), other.end(), m_Data);
            return *this;
        }

        Array& operator=(Array&& other) noexcept
        {
            if (this == &other)
                return *this;
            m_Data = (PointerType)malloc(other.m_Allocated);
            std::move(other.begin(), other.end(), m_Data);
            free(other.m_data);
            return *this;
        }

   
        ~Array() override
        {
            free(m_Data);
            m_Count = -1;
            m_Allocated = 0;
        }

    public:
        void Add(ConstRefType Element)
        {
            if(m_Count + 1 > m_Allocated)
            {
                m_Allocated *= 2;
                PointerType New = (PointerType)realloc(m_Data, m_Allocated * sizeof(T));
                if(!New)
                {
                    HYDRO_LOG(DynamicArray, Verbosity::Error, "Failed to reallocate dynamic array!");
                    return;
                }
                m_Data = New;
            }

            m_Data[m_Count] = Element;
            m_Count += 1;
        }

        void AddRange(const Buffer<ElementType>& Elements)
        {
            for(const T* It = Elements.begin(); It != Elements.end(); ++It)
            {
                Add(*It);
            }
        }

        void AddRange(const std::initializer_list<ElementType>& List)
        {
            for(const auto& Elem : List)
            {
                Add(Elem);
            }
        }
        

        size_t IndexOf(ConstRefType Element)
        {
            auto It = std::ranges::find(begin(), end(), Element);
            if(!It) return -1;
            return It - m_Data;
        }

        void Remove(ConstRefType Element)
        {
            const auto It = std::ranges::find(begin(), end(), Element);
            if(!It || It < begin() || It > end() || It + 1 > end()) return;
            std::move(It + 1, end(), It);
            m_Count -= 1;
        }

        RefType operator[](size_t Index)
        {
            return m_Data[Index];
        }

        ConstRefType operator[](size_t Index) const
        {
            return m_Data[Index];
        }

        

        Iterator begin() override { return Iterator(m_Data); }
        Iterator end() override { return Iterator(m_Data + m_Count); }

        ConstIterator begin() const override { return ConstIterator(m_Data); }
        ConstIterator end() const override { return ConstIterator(m_Data + m_Count); }

        SizeType Count() const { return m_Count; }
        bool IsEmpty() const { return m_Count == 0; }

        void Reset()
        {
            HYDRO_MEMSET(m_Data, 0, m_Allocated);
            m_Count = 0;
        }

        PointerType Last() const
        {
            if(m_Count == 0) return nullptr;
            return &m_Data[m_Count];
        }
    private:
        PointerType m_Data = nullptr;
        size_t m_Allocated = 0;
        size_t m_Count = 0;
    };
}
