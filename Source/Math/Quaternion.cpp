#include "Quaternion.h"
#include "Functions.h"
#include "Vector3.h"

namespace Hydro
{
    Quaternion Quaternion::One = { 1.0f, 1.0f, 1.0f, 1.0f };
    Quaternion Quaternion::Identity = { 1.0f, 0.0f, 0.0f, 0.0f };
    Quaternion::Quaternion(f32 W, f32 X, f32 Y, f32 Z): w(W), x(X), y(Y), z(Z){}

    f32 Quaternion::Magnitude() const
    {
        return Math::Sqrt(x*x + y*y + z*z + w*w);
    }

    Quaternion Quaternion::Normalized() const
    {
        return { x / Magnitude(), y / Magnitude(), z / Magnitude(), w / Magnitude() };
    }

    Quaternion Quaternion::Conjugated() const
    {
        return { -x, -y, -z, w};
    }

    Quaternion Quaternion::Inversed() const
    {
        return this->Conjugated().Normalized();
    }

    f32 Quaternion::Dot(const Quaternion& Other)
    {
        return 0.0f;
    }

    Quaternion Quaternion::Multiply(const Quaternion& Other) const
    {
        Quaternion Result = Identity;
        Result.x =  x * Other.w +
                    y * Other.z -
                    z * Other.y +
                    w * Other.x;

        Result.y =  -x * Other.z +
                    y * Other.w +
                    z * Other.x +
                    w * Other.y;

        Result.z =  x * Other.y -
                    y * Other.x +
                    z * Other.w +
                    w * Other.z;
        
        Result.w =  -x * Other.x -
                    y * Other.y -
                    z * Other.z +
                    w * Other.w;
        return Result;
    }
}
