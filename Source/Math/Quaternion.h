#pragma once
#include "Core/NumericTypes.h"

namespace Hydro
{
    class Vector3;
    
    class Quaternion
    {
    public:
        Quaternion(f32 W, f32 X, f32 Y, f32 Z);
        f32 Magnitude() const;
        Quaternion Normalized() const;
        Quaternion Conjugated() const;
        Quaternion Inversed() const;
        f32 Dot(const Quaternion& Other);
        Quaternion Multiply(const Quaternion& Other) const;
        static Quaternion One;
        static Quaternion Identity;
    private:
        f32 w, x, y, z;
    };
}

