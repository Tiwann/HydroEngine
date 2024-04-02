#include "HydroPCH.h"
#include "Functions.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Hydro
{
    float Math::Cos(float Val)
    {
        return std::cos(Val);
    }

    float Math::Sin(float Val)
    {
        return std::sin(Val);
    }

    float Math::Tan(float Val)
    {
        return std::tan(Val);
    }

    float Math::Arccos(float Val)
    {
        return std::acos(Val);
    }

    float Math::Arcsin(float Val)
    {
        return std::asin(Val);
    }

    float Math::Arctan(float Val)
    {
        return std::atan(Val);
    }

    float Math::Abs(float Value)
    {
        return Value > 0 ? Value : -Value;
    }

    float Math::Clamp(float Value, float Min, float Max)
    {
        return Value < Min ? Min : Value > Max ? Max : Value;
    }

    float Math::Lerp(float A, float B, float Alpha)
    {
        return A + (B - A) * Alpha;
    }

    float Math::Map(float Value, float MinA, float MaxA, float MinB, float MaxB)
    {
        return MinB + (MaxB - MinB) * ((Value - MinA) / (MaxA - MinA));
    }

    float Math::Floor(float Value)
    {
        return std::floor(Value);
    }

    float Math::Ceil(float Value)
    {
        return std::ceil(Value);
    }

    float Math::Smoothstep(float Value, float Min, float Max)
    {
        const float Val = Clamp((Value - Min) / (Max - Min), 0.0f, 1.0f);
        return Val * Val * (3.0f - 2.0f * Val);
    }

    float Math::MappedSin(float Val, float Min, float Max)
    {
        return Map(Sin(Val), -1.0f, 1.0f, Min, Max);
    }

    float Math::MappedCos(float Val, float Min, float Max)
    {
        return Map(Cos(Val), -1.0f, 1.0f, Min, Max);
    }

    float Math::Distance(const Vector2& VecA, const Vector2& VecB)
    {
        return Sqrt(Pow(VecB.x - VecA.x, 2) + Pow(VecB.y - VecA.y, 2));
    }

    float Math::Distance(const Vector3& VecA, const Vector3& VecB)
    {
        return Sqrt(Pow(VecB.x - VecA.x, 2) + Pow(VecB.y - VecA.y, 2) + Pow(VecB.z - VecA.z, 2));
    }

    
    bool Math::AreSame(float Lhs, float Rhs)
    {
        return Abs(Lhs - Rhs) <= std::numeric_limits<float>::epsilon();
    }

    bool Math::IsZero(float Val)
    {
        return AreSame(Val, 0.0f);
    }

    float Math::Sqrt(float Val)
    {
        return std::sqrt(Val);
    }

    float Math::Pow(float Val, float Exp)
    {
        return std::pow(Val, Exp);
    }

    float Math::Radians(float Degrees)
    {
        return Degrees * Pi / 180.0f;
    }

    float Math::Degrees(float Radians)
    {
        return Radians * 180.0f / Pi;
    }
    

}
