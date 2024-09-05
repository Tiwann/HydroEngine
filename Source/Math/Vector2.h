#pragma once
#include "Core/NumericTypes.h"
#include <nlohmann/json_fwd.hpp>

struct b2Vec2;
struct ImVec2;

namespace Hydro
{
    class Vector3;
    
    class Vector2
    {
    public:
        union{ f32 x{0.0f}, r; };
        union{ f32 y{0.0f}, g; };

        Vector2() = default;
        Vector2(f32 X, f32 Y);
        Vector2(f32 Value);
        Vector2(const Vector3& Vec);
        Vector2(const b2Vec2& Vec);
        Vector2(const ImVec2& Vec);
        
        f32 Magnitude() const;
        f32* ValuePtr();
        f32 Dot(const Vector2& Vec) const;

        Vector2 WithX(f32 X) const;
        Vector2 WithY(f32 Y) const;
        Vector2 Normalized() const;
        Vector2 operator+(const Vector2& Vec) const;
        Vector2 operator-(const Vector2& Vec) const;
        Vector2 operator-() const;

        operator b2Vec2() const;
        operator ImVec2() const;

        Vector2 operator/(f32 Scalar);
        friend Vector2 operator*(f32 Scalar, const Vector2& Vec);
        friend Vector2 operator*(const Vector2& Vec, f32 Scalar);
        
        Vector2& operator*=(f32 Scalar);
        Vector2& operator+=(const Vector2& Vec);
        bool operator==(const Vector2& Vec) const;
        Vector2 operator*(const Vector2& Vec) const;


        static Vector2 Zero;
        static Vector2 One;
        static Vector2 Right;
        static Vector2 Up;
        static Vector2 Left;
        static Vector2 Down;
    };

    void to_json(nlohmann::json& j, const Vector2& Vec);
    void from_json(const nlohmann::json& j, Vector2& Vec);
}
