#pragma once
#include "HydroPCH.h"
#include "Assertion.h"

namespace Hydro {
    template<typename Type>
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
            StringBase buffer = *this;
            delete[] m_Data;
            m_Data = new Type[alloc];
            std::memcpy(m_Data, buffer.m_Data, buffer.m_Size * sizeof(Type));
            std::memcpy(m_Data + m_Size, string.m_Data, string.m_Allocated * sizeof(Type));
            m_Size = new_size;
            m_Allocated = alloc;
            return *this;
        }

        Type operator[](uint32_t index)
        {
            HYDRO_ASSERT(index > 0 && index < m_Size, "Index out of bound!");
            return m_Data[index];
        }
        
        bool IsEmpty() const { return !m_Data; }
        
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

        void Erase(size_t position, size_t length) 
        {
            const bool bounds = position > 0 || position < m_Size || length > 0 || position + length < m_Size;
            HYDRO_ASSERT(bounds, "Out of bounds!");

            const size_t newSize = m_Size - length;
            const size_t alloc = m_Size + 1;
            Type* buffer = new Type[alloc];
            std::memcpy(buffer, m_Data + position, position);
            std::memcpy(buffer + position, m_Data + length, m_Size - length);
            buffer[newSize] = 0;
            delete[] m_Data;
            *this = { buffer };
        }

        StringBase SubString(size_t position, size_t length) const
        {
            const bool bounds = position > 0 || position <= m_Size || length > 0 || position + length < m_Size;
            HYDRO_ASSERT(bounds, "Out of bounds!");
            
            Type* buffer = new Type[length + 1];
            std::memcpy(buffer, m_Data + position, length);
            buffer[length] = (Type)0;
            StringBase str(buffer);
            delete[] buffer;
            return str;
        }
        

        size_t Find(const StringBase& string) const
        {
            if(const Type* find = std::strstr(m_Data, string.m_Data))
            {
                size_t i = 0;
                Type* ptr = m_Data;
                while(ptr != find)
                {
                    i++;
                    ++ptr;
                }
                return i;
            }
            else
            {
                return -1;
            }
        }

        bool EndsWith(const StringBase& string) const
        {
            Type* ptr = m_Data;
            uint32_t i = 0;
            
                
            while(*ptr++ != string.m_Data[0])
                i++;

            if(i == 0) return false;

            for(size_t j = 0; j < string.m_Size; j++)
            {
                const char left = m_Data[i + j];
                const char right = string.m_Data[j];
                if(left != right)
                    return false;
            }
            return true;
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


