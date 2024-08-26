#pragma once
#include "Core/Iterator.h"
#include <initializer_list>
#include <algorithm>

namespace Hydro
{
    template<typename Type>
    class Buffer
    {
    public:
        using Iterator = Iterator<Type>;
        using ConstIterator = ConstIterator<Type>;
        
        Buffer(Type* buffer, size_t Count)
        {
            Allocate(Count);
            std::copy(buffer, buffer + m_Count, m_Data);
        }

        Buffer(const std::initializer_list<Type>& List)
        {
            Allocate(List.size());
            std::copy(List.begin(), List.end(), m_Data);
        }

        Buffer(const Buffer& Buffer)
        {
            Allocate(Buffer.Count());
            std::copy(Buffer.GetData(), Buffer.GetData() + Buffer.Count(), m_Data);
        }

        Buffer(Buffer&& Other) noexcept
        {
            m_Data = Other.m_Data;
            m_Count = Other.m_Count;
            Other.m_Data = nullptr;
            Other.m_Count = 0;
        }

        Buffer& operator=(const Buffer& Other)
        {
            if(this == &Other)
                return *this;

            Allocate(Other.Count());
            std::copy(Other.GetData(), Other.GetData() + Other.Count(), m_Data);
            return *this;
        }

        Buffer& operator=(Buffer&& Other)
        {
            if(this == &Other)
                return *this;

            m_Data = Other.m_Data;
            m_Count = Other.m_Count;
            Other.m_Data = nullptr;
            Other.m_Count = 0;
            return *this;
        }

        

        Buffer(size_t Count)
        {
            Allocate(Count);
        }

        Buffer() = default;
        
        Type* GetData()
        {
            return m_Data;
        }
        
        const Type* GetData() const
        {
            return m_Data;
        }
        
        size_t Count() const
        {
            return m_Count;
        }
        
        size_t Size() const
        {
            return m_Count * sizeof(Type);
        }
        

        void Allocate(size_t Count)
        {
            if(m_Data && Count != 0)
                delete[] m_Data;
            m_Data = new Type[Count];
            m_Count = Count;
        }
        
        void Free()
        {
            delete[] m_Data;
            m_Data = nullptr;
        }

        const Type& operator[](size_t Index) const
        {
            return m_Data[Index];
        }

        Type& operator[](size_t Index)
        {
            return m_Data[Index];
        }

        Iterator begin() { return m_Data; }
        Iterator end() { return m_Data + m_Count; }
        ConstIterator begin() const { return m_Data; }
        ConstIterator end() const { return m_Data + m_Count; }
    private:
        Type* m_Data{nullptr};
        size_t m_Count{0};
    };

    
    template<typename Type>
    class ScopedBuffer
    {
    public:
        ScopedBuffer(const Buffer<Type>& Buff) : m_Buffer(Buff)
        {
            
        }

        ScopedBuffer() = default;


        ~ScopedBuffer()
        {
            Free();
        }
        
        
        const Type* GetData() const
        {
            return m_Buffer.GetData();
        }
        
        size_t Count() const
        {
            return m_Buffer.Count();
        }
        
        size_t Size() const
        {
            return m_Buffer.Size();
        }
        
        
        void Free()
        {
            m_Buffer.Free();
        }

        Buffer<Type>& AsBuffer() { return m_Buffer; }

        const Type* Begin() const { return m_Buffer.Begin(); }
        const Type* End() const { return m_Buffer.End(); }
    private:
        Buffer<Type> m_Buffer;
    };


    template<typename Type>
    class BufferView 
    {
    public:
        using Iterator = typename Buffer<Type>::Iterator;
        using ConstIterator = typename Buffer<Type>::Iterator;
        
        BufferView(const Type* Data, size_t Count) : m_Data(const_cast<Type*>(Data)), m_Count(Count){}
        BufferView(const Buffer<Type>& Buff) : m_Data(const_cast<Type*>(Buff.GetData())), m_Count(Buff.Count()){}
        BufferView(const BufferView& Buff) : m_Data(Buff.m_Data), m_Count(Buff.m_Count){}

        BufferView& operator=(const BufferView& Buff)
        {
            m_Data = Buff.m_Data;
            m_Count = Buff.m_Count;
            return *this;
        }
        
        ConstIterator Begin() const { return m_Data; }
        ConstIterator End() const { return m_Data + m_Count; }

        template<typename OtherType>
        BufferView<OtherType> As() const
        {
            return BufferView<OtherType>((OtherType*)GetData(), Count() * (sizeof(Type) / sizeof(OtherType)));
        }
        
        size_t Count() const
        {
            return m_Count;
        }
        
        size_t Size() const
        {
            return m_Count * sizeof(Type);
        }
        
        const Type& operator[](size_t Index) const
        {
            return m_Data[Index];
        }

        Type& operator[](size_t Index)
        {
            return m_Data[Index];
        }
        

        const Type* GetData() const { return m_Data; }

        void CopyTo(Buffer<Type>& Out) const
        {
            Out.Allocate(m_Count);
            std::copy(m_Data, m_Data + m_Count, Out.GetData());
        }
    private:
        Type* m_Data;
        size_t m_Count;
    };
    
}
