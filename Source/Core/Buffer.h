#pragma once


namespace Hydro
{
    template<typename Type>
    class Buffer
    {
    public:
        Buffer(Type* buffer, size_t count) : m_Count(count)
        {
            Allocate(m_Count);
            std::copy(buffer, buffer + m_Count, m_Data);
        }

        Buffer(const Buffer& Buffer)
        {
            Allocate(Buffer.Count());
            std::copy(Buffer.GetData(), Buffer.GetData() + Buffer.Count(), m_Data);
        }

        Buffer(size_t Count) : m_Count(Count)
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
        
        const Type* Begin() const { return m_Data; }
        const Type* End() const { return m_Data + m_Count; }
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
        using Iterator = Type*;
        using ConstIterator = const Type*;
        BufferView(const Type* Data, size_t Count) : m_Data(const_cast<Type*>(Data)), m_Count(Count){}
        BufferView(Type* Data, size_t Count) : m_Data(Data), m_Count(Count){}
        BufferView(Iterator Begin, Iterator End) : m_Data(Begin), m_Count(End - Begin){}
        BufferView(ConstIterator Begin, ConstIterator End) : m_Data(const_cast<Type*>(Begin)), m_Count(const_cast<Type*>(End) - const_cast<Type*>(Begin)){}
        BufferView(const Buffer<Type>& Buff) : m_Data(const_cast<Type*>(Buff.GetData())), m_Count(Buff.Count()){}
        
        ConstIterator Begin() const { return m_Data; }
        ConstIterator End() const { return m_Data + m_Count; }

        template<typename OtherType>
        BufferView<OtherType> As()
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

        const Type* GetData() const { return m_Data; }

        void CopyTo(Buffer<Type>& Out) const
        {
            Out.Allocate(m_Count);
            std::copy(m_Data, m_Data + m_Count, Out.GetData());
        }

        Iterator begin() const { return m_Data; }
        Iterator end() const { return m_Data; }
    private:
        Type* m_Data;
        size_t m_Count;
    };
    
}
