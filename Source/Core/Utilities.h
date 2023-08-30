#pragma once


namespace Hydro
{
    template<typename T>
    T Map(T val, T min_first_range, T max_first_range, T min_last_range, T max_last_range)
    {
        return min_last_range + (max_last_range - min_last_range) * ((val - min_first_range) / (max_first_range - min_first_range));
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
        return a + b(t - a);
    }

    template<typename T>
    constexpr T Flip(T val)
    {
        return 1 - val;
    }
    
}
