#pragma once
#include "Vector2.h"

namespace Hydro
{
    class Matrix2
    {
    public:
        Matrix2();
        Matrix2(const Vector2& Col1, const Vector2& Col2);


        const float* ValuePtr() const;
        float Magnitude() const;
        float Determinant() const;

        Vector2 Multiply(const Vector2& Vec) const;
        Vector2 operator*(const Vector2& Vec) const;
        Matrix2 Multiply(const Matrix2& Mat) const;
        Matrix2 operator*(const Matrix2& Mat) const;
        
        Vector2& operator[](size_t i);

        const Vector2& operator[](size_t i) const;
        Matrix2& operator*(float Scalar);

        void Rotate(float Radians);
        void RotateDegrees(float Degrees);
        void Scale(float Scalar);
        void Scale(const Vector2& Scale);
        
        static Matrix2 Identity;
        static Matrix2 One;
    private:
        union
        {
            Vector2 Columns[2];
            struct { float m00, m10, m01, m11; };
        };
    };
}
