#include "HydroPCH.h"
#include "Quaternion.h"
#include "Functions.h"
#include "Vector3.h"

namespace Hydro
{
    Quaternion Quaternion::One = { 1.0f, 1.0f, 1.0f, 1.0f };
    Quaternion Quaternion::Identity = { 1.0f, 0.0f, 0.0f, 0.0f };
    Quaternion::Quaternion(float W, float X, float Y, float Z): w(W), x(X), y(Y), z(Z){}

    Quaternion::Quaternion(Vector3 Vec) : w(0.0f), x(Vec.x), y(Vec.y), z(Vec.z) {}

    Quaternion Quaternion::Conjugate() const
    {
        return {w, -x, -y, -z};
    }

    Quaternion Quaternion::Opposite() const
    {
        return {-w, -x, -y, -z};
    }

    Quaternion Quaternion::Inverse() const
    {
        Quaternion Conj = Conjugate();
        Conj.w /= Magnitude();
        Conj.x /= Magnitude();
        Conj.y /= Magnitude();
        Conj.z /= Magnitude();
        return Conj;
    }

    float Quaternion::Magnitude() const
    {
        return Math::Sqrt(w*w + x*x + y*y + z*z);
    }

    Quaternion Quaternion::Add(const Quaternion& Quat) const
    {
        return { w + Quat.w, x + Quat.x, y + Quat.y, z + Quat.z };
    }

    Quaternion Quaternion::operator+(const Quaternion& Quat) const
    {
        return Add(Quat);
    }

    Quaternion Quaternion::Multiply(const Quaternion& Quat) const
    {
        return {
            w*Quat.w - x*Quat.x - y*Quat.y - z*Quat.z,
            w*Quat.x + x*Quat.w - y*Quat.z + z*Quat.y,
            w*Quat.y + x*Quat.z + y*Quat.w - z*Quat.x,
            w*Quat.z - x*Quat.y + y*Quat.z + z*Quat.w
        };
    }

    Quaternion Quaternion::operator*(const Quaternion& Quat) const
    {
        return Multiply(Quat);
    }

    Vector3 Quaternion::AsVector3() const
    {
        return {x, y, z};
    }

    Vector3 Quaternion::Rotate(const Vector3& Vec) const
    {
        const Quaternion Intermediate = Multiply(Vec);
        return Intermediate.Multiply(Conjugate()).AsVector3();
    }
}
