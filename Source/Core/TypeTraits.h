#pragma once
#include <cstdint>

namespace Hydro
{
    template<bool Val>
    struct BooleanConstant
    {
        static constexpr bool Value = Val;
    };
    
    struct TrueType : BooleanConstant<true> {};
    
    struct FalseType : BooleanConstant<false> {};

    template<typename T>
    struct IsInteger : FalseType{};

    template<>
    struct IsInteger<int8_t> : TrueType{};

    template<>
    struct IsInteger<int16_t> : TrueType{};

    template<>
    struct IsInteger<int32_t> : TrueType{};

    template<>
    struct IsInteger<int64_t> : TrueType{};


    template<>
    struct IsInteger<uint8_t> : TrueType{};

    template<>
    struct IsInteger<uint16_t> : TrueType{};

    template<>
    struct IsInteger<uint32_t> : TrueType{};

    template<>
    struct IsInteger<uint64_t> : TrueType{};

    template<typename T>
    static inline constexpr bool IsIntegerValue = IsInteger<T>::Value;


    template<typename T>
    struct IsFloatingPoint : FalseType {};
    
    template<>
    struct IsFloatingPoint<float> : TrueType{};

    template<>
    struct IsFloatingPoint<double> : TrueType{};

    template<typename T>
    static inline constexpr bool IsFloatingPointValue = IsFloatingPoint<T>::Value;

    template<typename T>
    static inline constexpr bool IsArithmeticValue = IsIntegerValue<T> || IsFloatingPointValue<T>;


    template<typename T>
    struct IsVector : FalseType {};
    
    template<>
    struct IsVector<class Vector2> : TrueType{};

    template<>
    struct IsVector<class Vector3> : TrueType{};

    template<>
    struct IsVector<class Vector4> : TrueType{};

    template<typename T>
    static constexpr bool IsVectorValue = IsVector<T>::Value;
    
    template <bool Condition, typename T = void>
    struct EnableIf {};
    
    template <typename T>
    struct EnableIf<true, T> { using Type = T; };

    template<bool Test, typename T = void>
    using EnableIfType = typename EnableIf<Test, T>::Type;
    
    template<typename Base, typename Derived>
    struct IsBaseOf : BooleanConstant<__is_base_of(Base, Derived)> {};

    template<typename Base, typename Derived>
    static constexpr bool IsBaseOfValue = IsBaseOf<Base, Derived>::Value;

    template<typename T>
    struct IsEnum : BooleanConstant<__is_enum(T)> {};

    template<typename T>
    static constexpr bool IsEnumValue = IsEnum<T>::Value;


    template<typename T>
    struct IsCharacter : FalseType {};

    template<>
    struct IsCharacter<char> : TrueType {};

    template<>
    struct IsCharacter<char8_t> : TrueType {};

    template<>
    struct IsCharacter<char16_t> : TrueType {};

    template<>
    struct IsCharacter<char32_t> : TrueType {};

    template<>
    struct IsCharacter<wchar_t> : TrueType {};
    
    template<typename T>
    static inline constexpr bool IsCharacterValue = IsCharacter<T>::Value;
    
}
