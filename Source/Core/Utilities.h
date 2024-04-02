#pragma once


namespace Hydro
{
    template<typename T>
    T Map(T Value, T MinA, T MaxA, T MinB, T MaxB)
    {
        return MinB + (MaxB - MinB) * ((Value - MinA) / (MaxA - MinA));
    }

    template<typename T>
    constexpr T Pi()
    {
        return (T)3.14159265359;
    }

    template<typename T>
    constexpr T PiHalf()
    {
        return Pi<T>() / (T)2.0;
    }
    
    template<typename T>
    constexpr T Tau()
    {
        return 2.0 * Pi<T>();
    }

    template<typename T>
    constexpr T Lerp(T a, T b, T t)
    {
        return a + (b - a) * t;
    }

    template<typename T>
    constexpr T Flip(T val)
    {
        return 1 - val;
    }

    template<typename T>
    T MappedSin(T X, T Min, T Max)
    {
        return Map(std::sin(X), -1.0f, 1.0f, Min, Max);
    }

    template<typename T>
    T Clamp(T Value, T Min, T Max)
    {
        return Value < Min ? Min : Value > Max ? Max : Value;
    }

    template<typename T>
    T Abs(T Value)
    {
        return Value < 0 ? -Value : Value;
    }
    
}
