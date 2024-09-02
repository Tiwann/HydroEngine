#pragma once
#include "TypeTraits.h"
#include <type_traits>

#define HYDRO_ENUM_TYPE_V(Type, Value) std::underlying_type_t<Type>(Value)
#define HYDRO_FLAG_APPEND(Left, Right) ((Left) | (Right))
#define HYDRO_FLAG_REMOVE(Left, Right) ((Left) & ~(Right))
#define HYDRO_FLAG_BIT(Name, Position) Name = 1 << Position


#define HYDRO_DECLARE_FLAGS(Enum, Name) \
    using Name = Hydro::Flags<Enum>; \
    \
    inline Enum operator|(Enum Lhs, Enum Rhs) \
    { \
        return static_cast<Enum>(HYDRO_ENUM_TYPE_V(Enum, Lhs) | HYDRO_ENUM_TYPE_V(Enum, Rhs)); \
    } \
    \
    inline Enum operator&(Enum Lhs, Enum Rhs) \
    { \
        return static_cast<Enum>(HYDRO_ENUM_TYPE_V(Enum, Lhs) & HYDRO_ENUM_TYPE_V(Enum, Rhs)); \
    }


namespace Hydro
{
    template <typename Enum, typename = EnableIfType<IsEnumValue<Enum>>>
    struct Flags
    {
        Flags() : m_Value((Enum)0){}
        Flags(Enum Val) : m_Value(Val){}
        explicit Flags(u32 Val) : m_Value((Enum)Val){}
        
        Flags Append(Flags Value)
        {
            m_Value = (Enum)HYDRO_FLAG_APPEND(HYDRO_ENUM_TYPE_V(Enum, m_Value), HYDRO_ENUM_TYPE_V(Enum, Value.m_Value));
            return m_Value;
        }

        Flags Remove(Flags Value)
        {
            m_Value = (Enum)HYDRO_FLAG_REMOVE(HYDRO_ENUM_TYPE_V(Enum, m_Value), HYDRO_ENUM_TYPE_V(Enum, Value.m_Value));
            return m_Value;
        }

        Flags Toggle(Flags Value)
        {
            return Contains(Value) ? Remove(Value) : Append(Value);
        }

        bool Contains(Flags Value)
        {
            return static_cast<bool>(HYDRO_ENUM_TYPE_V(Enum, m_Value) & HYDRO_ENUM_TYPE_V(Enum, Value.m_Value));
        }

        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        T As() const { return (T)HYDRO_ENUM_TYPE_V(Enum, m_Value); }

        bool operator==(const Enum& Other) const
        {
            return m_Value == Other;
        }

        Flags operator|(Flags Other)
        {
            return Append(Other);
        }

        Flags& operator|=(Flags Other)
        {
            Append(Other);
            return *this;
        }
        
        operator Enum()
        {
            return m_Value;
        }

        

    private:
        Enum m_Value = 0; 
    };
    
}

    