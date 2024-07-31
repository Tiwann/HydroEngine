#pragma once
#include "Functions.h"

namespace Hydro
{
    class Color;
    class Vector3;
    
    class Vector4
    {
    public:
        union{ float x{0.0f}, r; };
        union{ float y{0.0f}, g; };
        union{ float z{0.0f}, b; };
        union{ float w{0.0f}, a; };

        Vector4() = default;
        Vector4(float X, float Y, float Z, float W);
        Vector4(float Value);
        Vector4(const Vector3& Vec);
        Vector4(const Vector3& Vec, float W);
        
        float Magnitude() const;
        float* ValuePtr();
        float Dot(const Vector4& Vec) const;

        Vector4 WithX(float X) const;
        Vector4 WithY(float Y) const;
        Vector4 WithZ(float Z) const;
        Vector4 WithW(float W) const;
        Vector4 Normalized() const;
        Vector4 operator+(const Vector4& Vec) const;
        Vector4 operator-(const Vector4& Vec) const;
        Vector4 operator-() const;

        friend Vector4 operator*(float Scalar, const Vector4& Vec);
        friend Vector4 operator*(const Vector4& Vec, float Scalar);
        Vector4 operator*(const Vector4& Vec) const;
        Vector4& operator*=(float Scalar);
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
}
