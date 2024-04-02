#pragma once

namespace Hydro
{
    class Vector3;
    
    class Quaternion
    {
    public:
        Quaternion(float W, float X, float Y, float Z);
        Quaternion(Vector3 Vec);
        
        Quaternion Conjugate() const;
        Quaternion Opposite() const;
        Quaternion Inverse() const;
        float Magnitude() const;

        Quaternion Add(const Quaternion& Quat) const;
        Quaternion operator+(const Quaternion& Quat) const;
        Quaternion Multiply(const Quaternion& Quat) const;
        Quaternion operator*(const Quaternion& Quat) const;

        Vector3 AsVector3() const;
        
        Vector3 Rotate(const Vector3& Vec) const;

        static Quaternion One;
        static Quaternion Identity;
    private:
        float w, x, y, z;
    };
}

