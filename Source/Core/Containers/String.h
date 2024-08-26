#pragma once
#include "StaticArray.h"
#include "Core/Iterator.h"
#include "Core/Assertion.h"
#include "Core/TypeTraits.h"

namespace Hydro
{

    template<typename CharacterType, typename = EnableIfType<IsCharacterValue<CharacterType>>>
    static size_t StringLength(const CharacterType* Data)
    {
        CharacterType* Ptr = const_cast<CharacterType*>(Data);
        size_t Count = 0;
        while (*Ptr != 0)
        {
            Count++;
            ++Ptr;
        }
        return Count;
    }
    
    template<typename T, typename = EnableIfType<IsCharacterValue<T>>>
    class StringBase : public Iterable<T>
    {
    public:
        using CharacterType = T;
        using SizeType = size_t;
        using StringLiteralType = const CharacterType*;
        using PointerType = CharacterType*;
        using Iterator = Iterator<T>;
        using ConstIterator = ConstIterator<T>;
        
        static inline const SizeType CharacterSize = sizeof(CharacterType);
        
        StringBase()
        {
            m_Data = new CharacterType[1]{};
            m_Count = 0;
        }
        
        StringBase(StringLiteralType Data)
        {
            HYDRO_ASSERT(Data, "Cannot construct string with nullptr!");
            m_Count = StringLength(Data);
            m_Data = new CharacterType[m_Count + 1]{};
            memcpy(m_Data, Data, m_Count * CharacterSize);
        }

        StringBase(CharacterType* Data, SizeType Count)
        {
            HYDRO_ASSERT(Data, "Cannot construct string with nullptr!");
            m_Count = Count;
            m_Data = new CharacterType[m_Count + 1]{};
            memcpy(m_Data, Data, m_Count * CharacterSize);
        }
        
        StringBase(const StringBase& Other)
        {
            delete[] m_Data;
            m_Data = new CharacterType[Other.m_Count + 1]{};
            memcpy(m_Data, Other.m_Data, Other.m_Count * CharacterSize);
            m_Count = Other.m_Count;
        }

        StringBase(StringBase&& Other) noexcept
        {
            m_Data = Other.m_Data;
            m_Count = Other.m_Count;
            Other.m_Data = nullptr;
            Other.m_Count = 0;
        }

        StringBase& operator=(const StringBase& Other)
        {
            if(this == &Other)
                return *this;

            if(m_Data) delete[] m_Data;
            m_Data = new CharacterType[Other.m_Count + 1]{};
            memcpy(m_Data, Other.m_Data, Other.m_Count * CharacterSize);
            m_Count = Other.m_Count;
            return *this;
        }

        StringBase& operator=(StringBase&& Other) noexcept
        {
            if(this == &Other)
                return *this;

            delete[] m_Data;
            
            m_Data = Other.m_Data;
            m_Count = Other.m_Count;
            Other.m_Data = nullptr;
            Other.m_Count = 0;
            return *this;
        }

        ~StringBase() override
        {
            delete[] m_Data;
            m_Count = 0;
        }

        template<size_t N>
        StaticArray<CharacterType, N> AsArray()
        {
            return {m_Data, m_Count};
        }

        CharacterType& operator[](SizeType Index)
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            return m_Data[Index];
        }
        
        const CharacterType& operator[](SizeType Index) const
        {
            HYDRO_ASSERT(Index <= m_Count, "Index out of bounds");
            return m_Data[Index];
        }

        bool operator==(const StringBase& Other) const
        {
            if(m_Count != Other.m_Count)
                return false;

            for(SizeType i = 0; i < m_Count; ++i)
                if(m_Data[i] != Other.m_Data[i])
                    return false;
            
            return true;
        }


        CharacterType* Data() { return m_Data; }
        const CharacterType* Data() const { return m_Data; }
        
        CharacterType* operator*() { return m_Data; }
        const CharacterType* operator*() const { return m_Data; }
        
        SizeType Count() const { return m_Count; }
        
        StringBase& Append(StringLiteralType Data)
        {
            HYDRO_ASSERT(Data, "Cannot apped string with nullptr string literal!");
            const SizeType DataCount = StringLength(Data);
            const SizeType NewCount = m_Count + DataCount;
            CharacterType* NewData = new CharacterType[NewCount + 1]{};
            memcpy(NewData, m_Data, m_Count * CharacterSize);
            memcpy(NewData + m_Count, Data, DataCount * CharacterSize);
            delete [] m_Data;
            m_Data = NewData;
            m_Count = NewCount;
            return *this;
        }

        
        StringBase& Append(CharacterType Character)
        {
            const SizeType NewCount = m_Count + 1;
            CharacterType* NewData = new CharacterType[NewCount + 1]{};
            memcpy(NewData, m_Data, m_Count * CharacterSize);
            memcpy(NewData + m_Count, &Character, CharacterSize);
            delete [] m_Data;
            m_Data = NewData;
            m_Count = NewCount;
            return *this;
        }

        StringBase& Append(const StringBase& String)
        {
            const SizeType DataCount = String.Count();
            const SizeType NewCount = m_Count + DataCount;
            CharacterType* NewData = new CharacterType[NewCount + 1]{};
            memcpy(NewData, m_Data, m_Count * CharacterSize);
            memcpy(NewData + m_Count, String.Data(), DataCount * CharacterSize);
            delete [] m_Data;
            m_Data = NewData;
            m_Count = NewCount;
            return *this;
        }
        
        StringBase Substring(SizeType Begin, SizeType End)
        {
            HYDRO_ASSERT(Begin < m_Count && Begin + End <= m_Count, "Indices out of bounds!");
            const SizeType NewCount = End - Begin + 1;
            CharacterType* NewData = new CharacterType[NewCount + 1]{};
            memcpy(NewData, m_Data + Begin, NewCount * CharacterSize);
            return {NewData, NewCount};
        }
        
        SizeType Find(CharacterType Char)
        {
            for(SizeType i = 0; i < m_Count; ++i)
            {
                if(m_Data[i] == Char)
                    return i;
            }
            return -1;
        }

        SizeType Find(const StringBase& Str)
        {
            return -1;
        }
        
        SizeType OccurrencesOf(CharacterType Char)
        {
            SizeType Result = 0;
            for(SizeType i = 0; i < m_Count; ++i)
            {
                CharacterType Curr = m_Data[i];
                if(Curr == Char)
                    Result++;
            }
            return Result; 
        }

        StringBase& Replace(const StringBase& From, const StringBase& To)
        {
            return *this;
        }

        
        

        Iterator begin() override { return m_Data; }
        Iterator end() override { return m_Data + m_Count; }
        ConstIterator begin() const override { return m_Data; }
        ConstIterator end() const override { return m_Data + m_Count; }
    
    private:
        CharacterType* m_Data = nullptr;
        size_t m_Count = 0;
    };
    
    using String = StringBase<char>;
    using String16 = StringBase<char16_t>;
    using String32 = StringBase<char32_t>;
    using WideString = StringBase<wchar_t>;
}

#include <spdlog/fmt/bundled/core.h>
#include <spdlog/fmt/bundled/format.h>

namespace Hydro
{
    template <typename... Args>
    String Format(fmt::format_string<Args...> Fmt, Args&&... Arguments)
    {
        return fmt::vformat(Fmt, fmt::make_format_args(Arguments...)).c_str();
    }
}

template<>
struct fmt::formatter<Hydro::String> : formatter<string_view>
{
    fmt::format_context::iterator format(const Hydro::String& Str, format_context& Context) const
    {
        return fmt::formatter<string_view>::format(string_view(Str.Data(), Str.Count()), Context);
    }
};




