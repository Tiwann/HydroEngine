#include "Vector2.h"
#include "Vector3.h"
#include "Functions.h"

#include <box2d/b2_math.h>
#include <imgui/imgui.h>
#include <nlohmann/json.hpp>


namespace Hydro
{
    Vector2 Vector2::Zero    = { 0.0f, 0.0f };
    Vector2 Vector2::One     = { 1.0f, 1.0f };
    Vector2 Vector2::Right   = { 1.0f, 0.0f };
    Vector2 Vector2::Up      = { 0.0f, 1.0f };
    Vector2 Vector2::Left    = { -1.0f, 0.0f };
    Vector2 Vector2::Down    = { 0.0f, -1.0f };
    

    Vector2::Vector2(f32 X, f32 Y): x(X), y(Y)
    {
    }

    Vector2::Vector2(f32 Value): x(Value), y(Value)
    {
    }

    Vector2::Vector2(const Vector3& Vec) : x(Vec.x), y(Vec.y)
    {
    }

    Vector2::Vector2(const b2Vec2& Vec) : x(Vec.x), y(Vec.y)
    {
    }

    Vector2::Vector2(const ImVec2& Vec) : x(Vec.x), y(Vec.y)
    {
    }

    f32 Vector2::Magnitude() const
    {
        return Math::Sqrt(x * x + y * y);
    }

    f32* Vector2::ValuePtr()
    {
        return (f32*)this;
    }

    f32 Vector2::Dot(const Vector2& Vec) const
    {
        return x * Vec.x + y * Vec.y;
    }

    f32 Vector2::Dot(const Vector2& VecA, const Vector2& VecB)
    {
        return VecA.Dot(VecB);
    }

    f32 Vector2::Angle(const Vector2& VecA, const Vector2& VecB)
    {
        return Math::Acos(VecA.Dot(VecB) / (VecA.Magnitude() * VecB.Magnitude()));
    }

    Vector2 Vector2::Lerp(const Vector2& A, const Vector2& B, f32 Alpha)
    {
        return A + B * Alpha - A * Alpha;
    }

    Vector2 Vector2::QuadraticBezier(const Vector2& A, const Vector2& B, const Vector2& C, f32 Alpha)
    {
        const Vector2 P0 = Lerp(A, B, Alpha);
        const Vector2 P1 = Lerp(B, C, Alpha);
        return Lerp(P0, P1, Alpha);
    }

    Vector2 Vector2::CubicBezier(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D, f32 Alpha)
    {
        const Vector2 P0 = QuadraticBezier(A, B, C, Alpha);
        const Vector2 P1 = QuadraticBezier(B, C, D, Alpha);
        return Lerp(P0, P1, Alpha);
    }

    Vector2 Vector2::WithX(f32 X) const
    {
        return {X, y};
    }

    Vector2 Vector2::WithY(f32 Y) const
    {
        return {x, Y};
    }

    Vector2 Vector2::Normalized() const
    {
        return {x / Magnitude(), y / Magnitude()};
    }

    Vector2 Vector2::operator+(const Vector2& Vec) const
    {
        return {x + Vec.x, y + Vec.y};
    }

    Vector2 Vector2::operator-(const Vector2& Vec) const
    {
        return {x - Vec.x, y - Vec.y};
    }

    Vector2 Vector2::operator-() const
    {
        return {-x, -y};
    }

    Vector2::operator b2Vec2() const
    {
        return {x, y};
    }

    Vector2::operator ImVec2() const
    {
        return {x, y};
    }

    Vector2 Vector2::operator/(f32 Scalar)
    {
        return { x / Scalar, y / Scalar };
    }

    Vector2 operator*(f32 Scalar, const Vector2& Vec)
    {
        return {Vec.x * Scalar, Vec.y * Scalar};
    }

    Vector2 operator*(const Vector2& Vec, f32 Scalar)
    {
        return {Vec.x * Scalar, Vec.y * Scalar};
    }

    Vector2& Vector2::operator*=(f32 Scalar)
    {
        x *= Scalar;
        y *= Scalar;
        return *this;
    }

    Vector2& Vector2::operator+=(const Vector2& Vec)
    {
        x *= Vec.x;
        y *= Vec.y;
        return *this;
    }

    bool Vector2::operator==(const Vector2& Vec) const
    {
        return Math::AreSame(x, Vec.x)
            && Math::AreSame(y, Vec.y);
    }

    Vector2 Vector2::operator*(const Vector2& Vec) const
    {
        return {x * Vec.x, y * Vec.y};
    }

    void to_json(nlohmann::json& j, const Vector2& Vec)
    {
        j = { {"x", Vec.x}, {"y", Vec.y} };
    }

    void from_json(const nlohmann::json& j, Vector2& Vec)
    {
        j["x"].get_to(Vec.x);
        j["y"].get_to(Vec.y);
    }
}
