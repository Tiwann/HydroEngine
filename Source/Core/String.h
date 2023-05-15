#pragma once
#include "HydroPCH.h"
#include <cstring>
#include <cstdint>
#include <ostream>


namespace Hydro {
    template<class Type>
    class HYDRO_API StringBase
    {
    private:
        Type* m_Data = nullptr;
        size_t m_Size = 0;
        size_t m_Allocated = 0;
    
    public:
        StringBase()
            : m_Data(nullptr), m_Size(0), m_Allocated(1)
        {
            m_Data = new Type[m_Allocated];
            m_Data[0] = Type(0);
        }
        
        StringBase(const Type* data)
        : m_Data(nullptr), m_Size(0), m_Allocated(0)
        {
            m_Size = StrLen(data);
            m_Allocated = m_Size + 1;
            m_Data = new Type[m_Allocated];
            std::memcpy(m_Data, data, m_Allocated * sizeof (Type));
        }
    
        StringBase(const StringBase& string)
        {
            m_Size = string.m_Size;
            m_Allocated = string.m_Allocated;
            m_Data = new Type[string.m_Allocated];
            std::memcpy(m_Data, string.m_Data, string.m_Allocated * sizeof(Type));
        }
    
        StringBase& operator=(const StringBase& string)
        {
            if(this == &string)
                return *this;
    
            m_Size = string.m_Size;
            m_Allocated = string.m_Allocated;
            m_Data = new Type[string.m_Allocated];
            std::memcpy(m_Data, string.m_Data, string.m_Allocated * sizeof(Type));
            return *this;
        }
    
        StringBase(StringBase&& string) noexcept
        {
            m_Size = string.m_Size;
            m_Allocated = string.m_Allocated;
            m_Data = new Type[string.m_Allocated];
            std::memcpy(m_Data, string.m_Data, string.m_Allocated * sizeof(Type));
    
            delete[] string.m_Data;
            string = StringBase();
        }
    
        StringBase& operator=(StringBase&& string) noexcept
        {
            if(this == &string) return *this;
            m_Size = string.m_Size;
            m_Allocated = string.m_Allocated;
            m_Data = new Type[string.m_Allocated];
            std::memcpy(m_Data, string.m_Data, string.m_Allocated * sizeof(Type));
    
            
            string.m_Size = 0;
            string.m_Allocated = 0;
            return *this;
            
        }
        
        ~StringBase()
        {
            delete[] m_Data;
        }
    
    
        size_t Size() const { return m_Size; }
        const Type* Data() const { return m_Data; }
        Type* Data() { return m_Data; }
    
        const Type* operator*() const { return m_Data; }
        
        StringBase& Append(const StringBase& string)
        {
            const size_t new_size = m_Size + string.m_Size;
            const size_t alloc = new_size + 1;
            StringBase buffer = *this;
            delete[] m_Data;
            m_Data = new Type[alloc];
            std::memcpy(m_Data, buffer.m_Data, buffer.m_Size * sizeof(Type));
            std::memcpy(m_Data + m_Size, string.m_Data, string.m_Allocated * sizeof(Type));
            m_Size = new_size;
            m_Allocated = alloc;
            return *this;
        }
    
        StringBase& operator+(const StringBase& string)
        {
            const size_t new_size = m_Size + string.m_Size;
            const size_t alloc = new_size + 1;
            m_Data = (Type*)::operator new[](alloc, m_Data);
            std::memcpy(m_Data + m_Size, string.m_Data, string.m_Allocated * sizeof(Type));
            m_Size = new_size;
            m_Allocated = alloc;
            return *this;
        }
        
        bool Empty() const { return m_Data; }
        
        void Reset(const Type* data = nullptr)
        {
            delete m_Data;
            if(!data)
            {
                m_Size = 0;
                m_Allocated = 1;
                m_Data = new Type[m_Allocated];
                m_Data[0] = Type(0);
                return;
            }
    
            m_Size = StrLen(data);
            m_Allocated = m_Size + 1;
            m_Data = new Type[m_Allocated];
            std::memcpy(m_Data, data, (m_Size + 1) * sizeof (Type));
        }
    
        friend std::ostream& operator<<(std::ostream& stream, const StringBase& string)
        {
            return stream << string.Data();
        }
    
    private:
        size_t StrLen(const Type* data)
        {
            size_t length = 0;
            Type* position = const_cast<Type*>(data);
            while(*position++ != 0) length++;
            return length;
        }
    };
    
    using String = StringBase<char>;
    using UString = StringBase<uint8_t>;
    using WString = StringBase<wchar_t>;
}


