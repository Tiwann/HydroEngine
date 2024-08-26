#pragma once
#include "Pair.h"
#include "DynamicArray.h"


namespace Hydro
{
    template<typename KeyType, typename ValueType, typename TPair = Pair<KeyType, ValueType>>
    class Map : public Iterable<TPair>
    {
    public:
        using PairType = TPair;
        using SizeType = typename Array<PairType>::SizeType;
        using Iterator = Iterator<PairType>;
        using ConstIterator = ConstIterator<PairType>;
        
        Map() = default;
        Map(const Array<PairType>& Array) : m_Data(Array){}
        Map(const Map&) = default;
        Map(Map&&) noexcept = default;
        Map& operator=(const Map&) = default;
        Map& operator=(Map&&) = default;

        
        ValueType& operator[](const KeyType& Key)
        {
            SizeType Index = FindKey(Key);
            if(Index == -1)
            {
                const PairType Pair{ .Key = Key };
                m_Data.Add(Pair);
                return m_Data.Last().Value;
            }
            return m_Data[Index].Value;
        }

        const ValueType& operator[](const KeyType& Key) const
        {
            SizeType Index = FindKey(Key);
            if(Index == -1)
            {
                const PairType Pair{ .Key = Key };
                m_Data.Add(Pair);
                return m_Data.Last().Value;
            }
            return m_Data[Index].Value;
        }

        SizeType FindKey(const KeyType& Key)
        {
            for(SizeType i = 0; i < m_Data.Count(); ++i)
            {
                const PairType& Pair = m_Data.GetAt(i);
                if(Key == Pair.Key)
                    return i;
            }
            return -1;
        }

        SizeType FindValue(const ValueType& Value)
        {
            for(SizeType i = 0; i < m_Data.Count(); ++i)
            {
                const PairType& Pair = m_Data.GetAt(i);
                if(Value == Pair.Value)
                    return i;
            }
            return -1;
        }

        bool Contains(const KeyType& Key)
        {
            return FindKey(Key) != -1;
        }

        SizeType Count() const { return m_Data.Count(); }

        PairType& GetAt(SizeType Index)
        {
            return m_Data.GetAt(Index);
        }

        const PairType& GetAt(SizeType Index) const
        {
            return m_Data.GetAt(Index);    
        }
        
        Iterator begin() override { return m_Data.begin(); }
        Iterator end() override { return m_Data.end(); }
        ConstIterator begin() const override { return m_Data.begin(); }
        ConstIterator end() const override { return m_Data.end(); }
    
    private:
        Array<PairType> m_Data;
    };
}
