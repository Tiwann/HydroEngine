#pragma once

namespace Hydro
{
    class Vector3;
    
    class Quaternion
    {
    public:
        Quaternion(float W, float X, float Y, float Z);
        float Magnitude() const;
        Quaternion Normalized() const;
        Quaternion Conjugated() const;
        Quaternion Inversed() const;
        float Dot(const Quaternion& Other);
        Quaternion Multiply(const Quaternion& Other) const;
        static Quaternion One;
        static Quaternion Identity;
    private:
        float w, x, y, z;
    };
}

