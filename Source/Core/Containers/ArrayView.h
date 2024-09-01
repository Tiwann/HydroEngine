#pragma once
#include "DynamicArray.h"

namespace Hydro
{
    template<typename T>
    class ArrayView
    {
        using ArrayType = Array<T>;
        using PointerType = typename ArrayType::PointerType;
        using ConstPointerType = typename ArrayType::ConstPointerType;
        using ConstReferenceType = typename ArrayType::ConstReferenceType;
        using SizeType = typename ArrayType::SizeType;
        using ConstIterator = typename ArrayType::ConstIterator;
    public:
        ArrayView() : m_Data(nullptr), m_Count(0) {}
        ArrayView(const ArrayType& Arr) : m_Data(Arr.Data()), m_Count(Arr.Count()){}
        ArrayView(const ArrayView&) = default;
        ArrayView(ArrayView&&) noexcept = default;
        ArrayView& operator=(const ArrayView&) = default;
        ArrayView& operator=(ArrayView&&) noexcept = default;

        ConstPointerType Data() const { return m_Data; }
        SizeType Count() const { return m_Count; }
        bool IsEmpty() const { return m_Count == 0; }

        ConstIterator begin() const { return m_Data; }
        ConstIterator end() const { return m_Data + m_Count; }

        ConstReferenceType operator[](SizeType Index) const { return m_Data[Index]; }

        bool operator==(const ArrayView& other) const
        {
            return m_Data == other.m_Data && m_Count == other.m_Count;
        }
    private:
        ConstPointerType m_Data = nullptr;
        SizeType m_Count = 0;
    };
}
