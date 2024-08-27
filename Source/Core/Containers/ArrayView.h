#pragma once
#include "DynamicArray.h"

namespace Hydro
{
    template<typename T>
    class StringViewBase
    {
        using ArrayType = Array<T>;
        using PointerType = typename ArrayType::PointerType;
        using ConstPointerType = typename ArrayType::ConstPointerType;
        using SizeType = typename ArrayType::SizeType;
        using ConstIterator = typename ArrayType::ConstIterator;
    public:
        StringViewBase(const ArrayType& Arr) : m_Data(Arr.Data()), m_Count(Arr.Count()){}
        StringViewBase(const StringViewBase&) = default;
        StringViewBase(StringViewBase&&) noexcept = default;
        StringViewBase& operator=(const StringViewBase&) = default;
        StringViewBase& operator=(StringViewBase&&) noexcept = default;

        ConstPointerType Data() const { return m_Data; }
        SizeType Count() const { return m_Count; }

        ConstIterator begin() const { return m_Data; }
        ConstIterator end() const { return m_Data + m_Count; }
    private:
        ConstPointerType m_Data = nullptr;
        SizeType m_Count = 0;
    };
}
