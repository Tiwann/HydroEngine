#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Functions.h"

#include <box2d/b2_math.h>
#include <Jolt/Jolt.h>
#include <nlohmann/json.hpp>

namespace Hydro
{
    Vector3 Vector3::Zero    = { 0.0f, 0.0f, 0.0f };
    Vector3 Vector3::One     = { 1.0f, 1.0f, 1.0f };
    Vector3 Vector3::Right   = { 1.0f, 0.0f, 0.0f };
    Vector3 Vector3::Up      = { 0.0f, 1.0f, 0.0f };
    Vector3 Vector3::Left    = { -1.0f, 0.0f, 0.0f };
    Vector3 Vector3::Down    = { 0.0f, -1.0f, 0.0f };
    Vector3 Vector3::Forward = { 0.0f, 0.0f, 1.0f };
    Vector3 Vector3::Backward = { 0.0f, 0.0f, -1.0f };
    

    Vector3::Vector3(f32 X, f32 Y, f32 Z): x(X), y(Y), z(Z)
    {
    }

    Vector3::Vector3(f32 Value): x(Value), y(Value), z(Value)
    {
    }

    Vector3::Vector3(const Vector2& Vec): x(Vec.x), y(Vec.y), z(0.0f)
    {
    }

    Vector3::Vector3(const Vector2& Vec, f32 Z) : x(Vec.x), y(Vec.y), z(Z)
    {
    }

    Vector3::Vector3(const Vector4& Vec) : x(Vec.x), y(Vec.y), z(Vec.z)
    {
    }

    Vector3::Vector3(const b2Vec3& Vec) : x(Vec.x), y(Vec.y), z(Vec.z)
    {
    }

    Vector3::Vector3(const JPH::Vec3& Vec) : x(Vec.GetX()), y(Vec.GetY()), z(Vec.GetZ())
    {
    }

    f32 Vector3::Magnitude() const
    {
        return Math::Sqrt(x * x + y * y + z*z);
    }

    f32* Vector3::ValuePtr()
    {
        return (f32*)this;
    }

    const f32* Vector3::ValuePtr() const
    {
        return (const f32*)this;
    }

    f32 Vector3::Dot(const Vector3& Vec) const
    {
        return x * Vec.x + y * Vec.y + z * Vec.z;
    }

    Vector3 Vector3::WithX(f32 X) const
    {
        return {X, y, z};
    }

    Vector3 Vector3::WithY(f32 Y) const
    {
        return {x, Y, z};
    }

    Vector3 Vector3::WithZ(f32 Z) const
    {
        return {x, y, Z};
    }

    Vector3 Vector3::Normalized() const
    {
        return {x / Magnitude(), y / Magnitude(), z / Magnitude()};
    }

    Vector3 Vector3::operator+(const Vector3& Vec) const
    {
        return {x + Vec.x, y + Vec.y, z + Vec.z};
    }

    Vector3 Vector3::operator-(const Vector3& Vec) const
    {
        return {x - Vec.x, y - Vec.y, z - Vec.z};
    }

    Vector3 Vector3::operator-() const
    {
        return {-x, -y, -z};
    }

    Vector3& Vector3::operator+=(const Vector3& Vec)
    {
        x += Vec.x;
        y += Vec.y;
        z += Vec.z;
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& Vec)
    {
        x -= Vec.x;
        y -= Vec.y;
        z -= Vec.z;
        return *this;
    }

    Vector3::operator b2Vec3() const
    {
        return {x, y, z};
    }

    Vector3::operator JPH::Vec3() const
    {
        return {x, y, z};
    }

    Vector3 Vector3::Apply(f32 (*Function)(f32)) const
    {
        return {Function(x), Function(y), Function(z)};
    }


    Vector3 operator/(f32 Scalar, const Vector3& Vec)
    {
        return {Scalar / Vec.x, Scalar / Vec.y, Scalar / Vec.z};
    }

    Vector3 operator/(const Vector3& Vec, f32 Scalar)
    {
        return {Vec.x / Scalar, Vec.y / Scalar, Vec.z / Scalar};
    }

    Vector3 operator*(f32 Scalar, const Vector3& Vec)
    {
        return {Vec.x * Scalar, Vec.y * Scalar, Vec.z * Scalar};
    }

    Vector3 operator*(const Vector3& Vec, f32 Scalar)
    {
        return {Vec.x * Scalar, Vec.y * Scalar, Vec.z * Scalar};
    }

    Vector3& Vector3::operator*=(f32 Scalar)
    {
        x *= Scalar;
        y *= Scalar;
        z *= Scalar;
        return *this;
    }

    Vector3& Vector3::operator*=(const Vector3& Vec)
    {
        x *= Vec.x;
        y *= Vec.y;
        z *= Vec.z;
        return *this;
    }

    Vector3& Vector3::operator/=(f32 Scalar)
    {
        x /= Scalar;
        y /= Scalar;
        z /= Scalar;
        return *this;
    }

    Vector3& Vector3::operator/=(const Vector3& Vec)
    {
        x /= Vec.x;
        y /= Vec.y;
        z /= Vec.z;
        return *this;
    }

    bool Vector3::operator==(const Vector3& Vec) const
    {
        return Math::AreSame(x, Vec.x)
            && Math::AreSame(y, Vec.y)
            && Math::AreSame(z, Vec.z);
    }

    Vector3 Vector3::Lerp(const Vector3& VecA, const Vector3& VecB, f32 Alpha)
    {
        return VecA + VecB * Alpha - VecA * Alpha;
    }
    

    f32 Vector3::Angle(const Vector3& VecA, const Vector3& VecB)
    {
        const f32 CosAngle = VecA.Dot(VecB) / (VecA.Magnitude() * VecB.Magnitude());
        return Math::Acos(CosAngle);
    }

    Vector3 Vector3::MoveTowards(const Vector3& Current, const Vector3& Target, f32 MaxDelta)
    {
        const Vector3 Direction = Target - Current;
        const f32 Distance = Direction.Magnitude();
        const Vector3 MovedVector = Current + Direction / Distance * MaxDelta;
        return Distance <= MaxDelta || Math::IsZero(Distance) ? Target : MovedVector;
    }

    Vector3 Vector3::SmoothDamp(const Vector3& Current, const Vector3& Target, Vector3& CurrentVelocity,
        f32 SmoothTime, f32 Delta, f32 MaxSpeed)
    {
        const f32 x = Math::SmoothDamp(Current.x, Target.x, CurrentVelocity.x, SmoothTime, Delta, MaxSpeed);
        const f32 y = Math::SmoothDamp(Current.y, Target.y, CurrentVelocity.y, SmoothTime, Delta, MaxSpeed);
        const f32 z = Math::SmoothDamp(Current.z, Target.z, CurrentVelocity.z, SmoothTime, Delta, MaxSpeed);
        return {x, y, z};
    }

    void to_json(nlohmann::json& j, const Vector3& Vec)
    {
        j = { {"x", Vec.x}, {"y", Vec.y}, {"z", Vec.z} };
    }

    void from_json(const nlohmann::json& j, Vector3& Vec)
    {
        j["x"].get_to(Vec.x);
        j["y"].get_to(Vec.y);
        j["z"].get_to(Vec.z);
    }
}
