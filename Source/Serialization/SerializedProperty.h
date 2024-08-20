#pragma once
#include "Serializable.h"
#include "Core/TypeTraits.h"

namespace Hydro
{
    template<typename T>
    class SerializedProperty
    {
    public:
        using ValueType = T;
        using ReferenceType = T&;
        using ForwardType = T&&;
        
        SerializedProperty(const ReferenceType Value) : m_Value(Value)
        {
            
        }

        SerializedProperty(ForwardType Value) noexcept : m_Value(std::move(Value))
        {
            
        }

        SerializedProperty(const SerializedProperty& Property) : m_Value(Property.m_Value)
        {
            
        }

        SerializedProperty(SerializedProperty&& Property) noexcept : m_Value(std::move(Property.m_Value)) 
        {
            
        }

        SerializedProperty& operator=(const ReferenceType Value)
        {
            m_Value = Value;
            return *this;
        }

        SerializedProperty& operator=(const SerializedProperty& Property)
        {
            if(this == &Property)
                return *this;

            m_Value = Property.m_Value;
            return *this;
        }

        SerializedProperty& operator=(ForwardType Value)
        {
            m_Value = std::move(Value);
            return *this;
        }

        SerializedProperty& operator=(SerializedProperty&& Property) noexcept
        {
            if(this == &Property)
                return *this;
            
            m_Value = std::move(Property.m_Value);
            return *this;
        }

        operator T() { return m_Value; }
    
    private:
        T m_Value;
    };
    
    
}
