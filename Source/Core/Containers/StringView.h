﻿#pragma once
#include "Core/TypeTraits.h"
#include "String.h"

namespace Hydro
{
    template<typename T, typename = EnableIfType<IsCharacterValue<T>>>
    class StringViewBase
    {
        using StringType = StringBase<T>;
        using CharacterType = typename StringType::CharacterType;
        using PointerType = typename StringType::PointerType;
        using ConstPointerType = const CharacterType*;
        using StringLiteralType = typename StringType::StringLiteralType;
        using SizeType = typename StringType::SizeType;
        using ConstIterator = typename StringType::ConstIterator;
    public:
        StringViewBase(const StringType& Str) : m_Data(const_cast<PointerType>(Str.Data())), m_Count(Str.Count()){}
        StringViewBase(ConstPointerType Data) : m_Data(const_cast<PointerType>(Data)), m_Count(StringLength(Data)){}
        StringViewBase(PointerType Data) : m_Data(Data), m_Count(StringLength(Data)){}
        StringViewBase(const StringViewBase&) = default;
        StringViewBase(StringViewBase&&) noexcept = default;
        StringViewBase& operator=(const StringViewBase&) = default;
        StringViewBase& operator=(StringViewBase&&) noexcept = default;

        ConstPointerType Data() const { return m_Data; }
        SizeType Count() const { return m_Count; }

        ConstIterator begin() const { return m_Data; }
        ConstIterator end() const { return m_Data + m_Count; }

        operator const CharacterType*() const { return m_Data; }
    private:
        PointerType m_Data = nullptr;
        SizeType m_Count = 0;
    };

    using StringView = StringViewBase<char>;
    using StringView16 = StringViewBase<char16_t>;
    using StringView32 = StringViewBase<char32_t>;
    using WideStringView = StringViewBase<wchar_t>;
}