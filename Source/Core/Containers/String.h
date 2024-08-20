#pragma once
#include "StaticArray.h"
#include "Core/Iterator.h"
#include "Core/Assertion.h"
#include "Math/Functions.h"

namespace Hydro
{
    template<typename T>
    constexpr bool IsCharacter = std::is_same_v<T, char> || std::is_same_v<T, char16_t> ||
            std::is_same_v<T, char32_t> || std::is_same_v<T, wchar_t>;
        
    template<typename T, typename = std::enable_if_t<IsCharacter<T>>>
    class StringBase : public Iterable<T>
    {
    public:
        using CharacterType = T;
        using SizeType = size_t;
        using StringLiteralType = const CharacterType*;
        using PointerType = CharacterType*;
        
        static inline const SizeType CharacterSize = sizeof(CharacterType);
        
        StringBase()
        {
            m_Data = new CharacterType[1]{};
            m_Count = 0;
        }
        
        StringBase(StringLiteralType Data)
        {
            HYDRO_ASSERT(Data, "Cannot construct string with nullptr!");
            m_Count = Length(Data);
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


        const CharacterType* Data() const { return m_Data; }
        
        SizeType Count() { return m_Count; }
        
        StringBase& Append(StringLiteralType Data)
        {
            HYDRO_ASSERT(Data, "Cannot apped string with nullptr string literal!");
            const SizeType DataCount = Length(Data);
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
        
        StringBase Substring(SizeType Begin, SizeType End)
        {
            HYDRO_ASSERT(Begin < m_Count && Begin + End <= m_Count, "Indices out of bounds!");
            const SizeType NewCount = End - Begin + 1;
            CharacterType* NewData = new CharacterType[NewCount + 1]{};
            memcpy(NewData, m_Data + Begin, NewCount * CharacterSize);
            return {NewData, NewCount};
        }
        
        SizeType IndexOf(CharacterType Char)
        {
            for(SizeType i = 0; i < m_Count; ++i)
            {
                if(m_Data[i] == Char)
                    return i;
            }
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

        const CharacterType* operator*() const { return m_Data; }
        

        Iterator<T> begin() override { return m_Data; }
        Iterator<T> end() override { return m_Data + m_Count; }
        ConstIterator<T> begin() const override { return m_Data; }
        ConstIterator<T> end() const override { return m_Data + m_Count; }

        template<typename ... Args>
        static StringBase Format(StringLiteralType Fmt, Args... Arguments)
        {
            return {};
        }

    private:
        CharacterType* m_Data = nullptr;
        size_t m_Count = 0;

        SizeType Length(StringLiteralType Data)
        {
            PointerType Ptr = const_cast<CharacterType*>(Data);
            SizeType Count = 0;
            while (*Ptr != 0)
            {
                Count++;
                ++Ptr;
            }
            return Count;
        }
    };
    
    using String = StringBase<char>;
    using String16 = StringBase<char16_t>;
    using String32 = StringBase<char32_t>;
    using WideString = StringBase<wchar_t>;

    
}
