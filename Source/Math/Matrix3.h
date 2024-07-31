#pragma once
#include "Vector3.h"

namespace Hydro
{
    class Matrix3
    {
    public:
        Matrix3();
        Matrix3(const Vector3& Col1, const Vector3& Col2, const Vector3& Col3);
        
        const float* ValuePtr() const;
        float Magnitude() const;
        float Determinant() const;

        Vector3 Multiply(const Vector3& Vec) const;
        Vector3 operator*(const Vector3& Vec) const;
        Matrix3 Multiply(const Matrix3& Mat) const;
        Matrix3 operator*(const Matrix3& Mat) const;
        
        Vector3& operator[](size_t i);

        const Vector3& operator[](size_t i) const;
        Matrix3& operator*(float Scalar);

        void Rotate(float Radians, const Vector3& Axis);
        void RotateDegrees(float Degrees, const Vector3& Axis);
        void Scale(float Scalar);
        void Scale(const Vector3& Scale);
        
        static Matrix3 Identity;
        static Matrix3 One;
    private:
        union
        {
            Vector3 Columns[3];
            struct { float m00, m10, m20, m01, m11, m21, m02, m12, m22; };
        };
    };
}
