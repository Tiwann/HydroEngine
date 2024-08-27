#include "Vector4.h"
#include "Vector3.h"
#include "Core/Color.h"
#include <nlohmann/json.hpp>
#include <Jolt/Jolt.h>
#include <Jolt/Math/Vec4.h>

namespace Hydro
{
    Vector4 Vector4::Zero    = { 0.0f, 0.0f, 0.0f, 0.0f };
    Vector4 Vector4::One     = { 1.0f, 1.0f, 1.0f, 1.0f };
    Vector4 Vector4::Right   = { 1.0f, 0.0f, 0.0f, 0.0f };
    Vector4 Vector4::Up      = { 0.0f, 1.0f, 0.0f, 0.0f };
    Vector4 Vector4::Left    = { -1.0f, 0.0f, 0.0f, 0.0f };
    Vector4 Vector4::Down    = { 0.0f, -1.0f, 0.0f, 0.0f };
    Vector4 Vector4::Forward = { 0.0f, 0.0f, 1.0f, 0.0f };
    Vector4 Vector4::Backward = { 0.0f, 0.0f, -1.0f, 0.0f };
    

    Vector4::Vector4(float X, float Y, float Z, float W): x(X), y(Y), z(Z), w(W)
    {
    }

    Vector4::Vector4(float Value): x(Value), y(Value), z(Value), w(Value)
    {
    }

    Vector4::Vector4(const Vector3& Vec): x(Vec.x), y(Vec.y), z(Vec.z), w(0.0f)
    {
    }

    Vector4::Vector4(const Vector3& Vec, float W) : x(Vec.x), y(Vec.y), z(Vec.z), w(W)
    {
    }

    Vector4::Vector4(const JPH::Vec4& Vec) : x(Vec.GetX()), y(Vec.GetY()), z(Vec.GetZ()), w(Vec.GetW())
    {
    }

    float Vector4::Magnitude() const
    {
        return Math::Sqrt(x * x + y * y + z * z + w * w);
    }

    float* Vector4::ValuePtr()
    {
        return (float*)this;
    }

    float Vector4::Dot(const Vector4& Vec) const
    {
        return x * Vec.x + y * Vec.y + z * Vec.z + w * Vec.w;
    }

    Vector4 Vector4::WithX(float X) const
    {
        return {X, y, z, w};
    }

    Vector4 Vector4::WithY(float Y) const
    {
        return {x, Y, z, w};
    }

    Vector4 Vector4::WithZ(float Z) const
    {
        return {x, y, Z, w};
    }

    Vector4 Vector4::WithW(float W) const
    {
        return {x, y, z, W};
    }
    
    Vector4 Vector4::Normalized() const
    {
        return {x / Magnitude(), y / Magnitude(), z / Magnitude(), w / Magnitude()};
    }

    Vector4 Vector4::operator+(const Vector4& Vec) const
    {
        return {x + Vec.x, y + Vec.y, z + Vec.z, w + Vec.w};
    }

    Vector4 Vector4::operator-(const Vector4& Vec) const
    {
        return {x - Vec.x, y - Vec.y, z - Vec.z, w - Vec.w};
    }

    Vector4 Vector4::operator-() const
    {
        return {-x, -y, -z, -w};
    }

    Vector4 operator*(float Scalar, const Vector4& Vec)
    {
        return {Vec.x * Scalar, Vec.y * Scalar, Vec.z * Scalar, Vec.w * Scalar};
    }

    Vector4 operator*(const Vector4& Vec, float Scalar)
    {
        return {Vec.x * Scalar, Vec.y * Scalar, Vec.z * Scalar, Vec.w * Scalar};
    }

    Vector4 Vector4::operator*(const Vector4& Vec) const
    {
        return { x * Vec.x, y * Vec.y, z * Vec.z, w * Vec.w};
    }

    Vector4& Vector4::operator*=(float Scalar)
    {
        x *= Scalar;
        y *= Scalar;
        z *= Scalar;
        w *= Scalar;
        return *this;
    }

    bool Vector4::operator==(const Vector4& Vec) const
    {
        return Math::AreSame(x, Vec.x)
            && Math::AreSame(y, Vec.y)
            && Math::AreSame(z, Vec.z);
    }

    Vector4::operator Color() const
    {
        return {r, g, b, a};
    }

    void to_json(nlohmann::json& j, const Vector4& Vec)
    {
        j = { {"x", Vec.x}, {"y", Vec.y}, {"z", Vec.z}, {"w", Vec.w} };
    }

    void from_json(const nlohmann::json& j, Vector4& Vec)
    {
        j["x"].get_to(Vec.x);
        j["y"].get_to(Vec.y);
        j["z"].get_to(Vec.z);
        j["w"].get_to(Vec.w);
    }
}
