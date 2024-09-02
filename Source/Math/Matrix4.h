#pragma once
#include "Vector4.h"

namespace JPH { class Mat44; }

namespace Hydro
{
    class Vector2;
    class Vector3;
    
    class Matrix4
    {
    public:
        Matrix4();
        Matrix4(const Vector4& Col1, const Vector4& Col2, const Vector4& Col3, const Vector4& Col4);
        Matrix4(const JPH::Mat44& Matrix);
        
        f32* ValuePtr();
        const f32* ValuePtr() const;

        const f32* operator*() const { return (const f32*)this; }
        f32* operator*() { return (f32*)this; }
        
        f32 Magnitude() const;
        f32 Determinant() const;
        Matrix4 Inverse() const;

        Vector4 Multiply(const Vector4& Vec) const;
        Vector4 operator*(const Vector4& Vec) const;
        Vector3 operator*(const Vector3& Vec) const;
        Vector2 operator*(const Vector2& Vec) const;
        
        Matrix4 Multiply(const Matrix4& Mat) const;
        Matrix4 operator*(const Matrix4& Mat) const;
        
        Vector4& operator[](size_t i);
        const Vector4& operator[](size_t i) const;
        Matrix4& operator*(f32 Scalar);

        void Rotate(f32 Radians, const Vector3& Axis);
        void Rotate(const Vector3& EulerAngles);
        void RotateDegrees(const Vector3& EulerAnglesDegrees);
        void RotateDegrees(f32 Degrees, const Vector3& Axis);
        void Scale(f32 Scalar);
        void Scale(const Vector3& Scale);
        void Translate(const Vector3& Translation);

        static Matrix4 Identity;
        static Matrix4 One;
    private:
        union
        {
            Vector4 Columns[4];
            struct { f32 m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33; };
        };
    };
}
