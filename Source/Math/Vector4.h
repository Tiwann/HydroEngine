#pragma once
#include "Core/NumericTypes.h"
#include <nlohmann/json_fwd.hpp>

namespace JPH { class Vec4; }

namespace Hydro
{
    class Color;
    class Vector3;
    
    class Vector4
    {
    public:
        union{ f32 x{0.0f}, r; };
        union{ f32 y{0.0f}, g; };
        union{ f32 z{0.0f}, b; };
        union{ f32 w{0.0f}, a; };

        Vector4() = default;
        Vector4(f32 X, f32 Y, f32 Z, f32 W);
        Vector4(f32 Value);
        Vector4(const Vector3& Vec);
        Vector4(const Vector3& Vec, f32 W);
        Vector4(const JPH::Vec4& Vec);
        
        f32 Magnitude() const;
        f32* ValuePtr();
        f32 Dot(const Vector4& Vec) const;

        Vector4 WithX(f32 X) const;
        Vector4 WithY(f32 Y) const;
        Vector4 WithZ(f32 Z) const;
        Vector4 WithW(f32 W) const;
        Vector4 Normalized() const;
        Vector4 operator+(const Vector4& Vec) const;
        Vector4 operator-(const Vector4& Vec) const;
        Vector4 operator-() const;

        friend Vector4 operator*(f32 Scalar, const Vector4& Vec);
        friend Vector4 operator*(const Vector4& Vec, f32 Scalar);
        Vector4 operator*(const Vector4& Vec) const;
        Vector4& operator*=(f32 Scalar);
        bool operator==(const Vector4& Vec) const;
        operator Color() const;

        static Vector4 Zero;
        static Vector4 One;
        static Vector4 Right;
        static Vector4 Up;
        static Vector4 Left;
        static Vector4 Down;
        static Vector4 Forward;
        static Vector4 Backward;
    };

    void to_json(nlohmann::json& j, const Vector4& Vec);
    void from_json(const nlohmann::json& j, Vector4& Vec);
}
