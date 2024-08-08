#include "HydroPCH.h"
#include "Matrix4.h"

#include "Vector3.h"
#include "Core/Assertion.h"

namespace Hydro
{
    Matrix4 Matrix4::Identity = Matrix4();
    Matrix4 Matrix4::One = { Vector4(1.0f), Vector4(1.0f), Vector4(1.0f), Vector4(1.0f) };
    
    Matrix4::Matrix4()
    {
        Columns[0] = {};
        Columns[1] = {};
        Columns[2] = {};
        Columns[3] = {};
        m00 = m11 = m22 = m33 = 1.0f;
    }

    Matrix4::Matrix4(const Vector4& Col1, const Vector4& Col2, const Vector4& Col3, const Vector4& Col4)
    {
        Columns[0] = Col1;
        Columns[1] = Col2;
        Columns[2] = Col3;
        Columns[3] = Col4;
    }

    float* Matrix4::ValuePtr()
    {
    	return (float*)this;
    }

    const float* Matrix4::ValuePtr() const
    {
        return (const float*)this;
    }

    float Matrix4::Magnitude() const
    {
        return Math::Sqrt(m00*m00 + m10*m10 + m20*m20 +
                          m01*m01 + m11*m11 + m21*m21 +
                          m02*m02 + m12*m12 + m22*m22);
    }

    float Matrix4::Determinant() const
    {
        //const Matrix2 X{{m11, m12}, {m21, m22}};
        //const Matrix2 Y{{m01, m02}, {m21, m22}};
        //const Matrix2 Z{{m01, m02}, {m11, m12}};
        //return m00 * X.Determinant() - m10 * Y.Determinant() + m20 * Z.Determinant();
        return 0.0f;
    }

    Matrix4 Matrix4::Inverse() const
    {
	    float Coef00 = Columns[2].z * Columns[3].w - Columns[3].z * Columns[2].w;
	    float Coef02 = Columns[1].z * Columns[3].w - Columns[3].z * Columns[1].w;
	    float Coef03 = Columns[1].z * Columns[2].w - Columns[2].z * Columns[1].w;

	    float Coef04 = Columns[2].y * Columns[3].w - Columns[3].y * Columns[2].w;
	    float Coef06 = Columns[1].y * Columns[3].w - Columns[3].y * Columns[1].w;
	    float Coef07 = Columns[1].y * Columns[2].w - Columns[2].y * Columns[1].w;

	    float Coef08 = Columns[2].y * Columns[3].z - Columns[3].y * Columns[2].z;
	    float Coef10 = Columns[1].y * Columns[3].z - Columns[3].y * Columns[1].z;
	    float Coef11 = Columns[1].y * Columns[2].z - Columns[2].y * Columns[1].z;

	    float Coef12 = Columns[2].x * Columns[3].w - Columns[3].x * Columns[2].w;
	    float Coef14 = Columns[1].x * Columns[3].w - Columns[3].x * Columns[1].w;
	    float Coef15 = Columns[1].x * Columns[2].w - Columns[2].x * Columns[1].w;

	    float Coef16 = Columns[2].x * Columns[3].z - Columns[3].x * Columns[2].z;
	    float Coef18 = Columns[1].x * Columns[3].z - Columns[3].x * Columns[1].z;
	    float Coef19 = Columns[1].x * Columns[2].z - Columns[2].x * Columns[1].z;

	    float Coef20 = Columns[2].x * Columns[3].y - Columns[3].x * Columns[2].y;
	    float Coef22 = Columns[1].x * Columns[3].y - Columns[3].x * Columns[1].y;
	    float Coef23 = Columns[1].x * Columns[2].y - Columns[2].x * Columns[1].y;

	    Vector4 Fac0(Coef00, Coef00, Coef02, Coef03);
	    Vector4 Fac1(Coef04, Coef04, Coef06, Coef07);
	    Vector4 Fac2(Coef08, Coef08, Coef10, Coef11);
	    Vector4 Fac3(Coef12, Coef12, Coef14, Coef15);
	    Vector4 Fac4(Coef16, Coef16, Coef18, Coef19);
	    Vector4 Fac5(Coef20, Coef20, Coef22, Coef23);

	    Vector4 Vec0(Columns[1].x, Columns[0].x, Columns[0].x, Columns[0].x);
	    Vector4 Vec1(Columns[1].y, Columns[0].y, Columns[0].y, Columns[0].y);
	    Vector4 Vec2(Columns[1].z, Columns[0].z, Columns[0].z, Columns[0].z);
	    Vector4 Vec3(Columns[1].w, Columns[0].w, Columns[0].w, Columns[0].w);

	    Vector4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
	    Vector4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
	    Vector4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
	    Vector4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

	    Vector4 SignA(+1, -1, +1, -1);
	    Vector4 SignB(-1, +1, -1, +1);
	    Matrix4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

	    Vector4 Row0(Inverse[0].x, Inverse[1].x, Inverse[2].x, Inverse[3].x);

	    Vector4 Dot0(Columns[0] * Row0);
	    float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

	    float OneOverDeterminant = 1.0f / Dot1;

	    return Inverse * OneOverDeterminant;
    }

    Vector4 Matrix4::Multiply(const Vector4& Vec) const
    {
        return Columns[0] * Vec.x + Columns[1] * Vec.y + Columns[2] * Vec.z;
    }

    Vector4 Matrix4::operator*(const Vector4& Vec) const
    {
        return Multiply(Vec);
    }

    Matrix4 Matrix4::Multiply(const Matrix4& Mat) const
    {
        Vector4 Col1 { Mat.m00 * m00 + Mat.m01 * m10 + Mat.m02 * m20 + Mat.m03 * m30,
                       Mat.m00 * m01 + Mat.m01 * m11 + Mat.m02 * m21 + Mat.m03 * m31,
                       Mat.m00 * m02 + Mat.m01 * m12 + Mat.m02 * m22 + Mat.m03 * m32,
                       Mat.m00 * m03 + Mat.m01 * m13 + Mat.m02 * m23 + Mat.m03 * m33, };
        
        Vector4 Col2 { Mat.m10 * m00 + Mat.m11 * m10 + Mat.m12 * m20 + Mat.m13 * m30,
                       Mat.m10 * m01 + Mat.m11 * m11 + Mat.m12 * m21 + Mat.m13 * m31,
                       Mat.m10 * m02 + Mat.m11 * m12 + Mat.m12 * m22 + Mat.m13 * m32, 
                       Mat.m10 * m03 + Mat.m11 * m13 + Mat.m12 * m23 + Mat.m13 * m33, };

        Vector4 Col3 { Mat.m20 * m00 + Mat.m21 * m10 + Mat.m22 * m20 + Mat.m23 * m30,
                       Mat.m20 * m01 + Mat.m21 * m11 + Mat.m22 * m21 + Mat.m23 * m31,
                       Mat.m20 * m02 + Mat.m21 * m12 + Mat.m22 * m22 + Mat.m23 * m32,
                       Mat.m20 * m03 + Mat.m21 * m13 + Mat.m22 * m23 + Mat.m23 * m33, };

        Vector4 Col4 { Mat.m20 * m00 + Mat.m31 * m10 + Mat.m32 * m20 + Mat.m33 * m30,
                       Mat.m20 * m01 + Mat.m31 * m11 + Mat.m32 * m21 + Mat.m33 * m31,
                       Mat.m20 * m02 + Mat.m31 * m12 + Mat.m32 * m22 + Mat.m33 * m32,
                       Mat.m20 * m03 + Mat.m31 * m13 + Mat.m32 * m23 + Mat.m33 * m33, };
        
        return { Col1, Col2, Col3, Col4 };
        
    }

    Matrix4 Matrix4::operator*(const Matrix4& Mat) const
    {
        return Multiply(Mat);
    }

    Vector4& Matrix4::operator[](size_t i)
    {
        HYDRO_ASSERT(i < 4, "Cannot access Mat4 element: index out of bounds.");
        return Columns[i];
    }

    const Vector4& Matrix4::operator[](size_t i) const
    {
        HYDRO_ASSERT(i < 4, "Cannot access Mat4 element: index out of bounds.");
        return Columns[i];
    }

    Matrix4& Matrix4::operator*(float Scalar)
    {
        Columns[0] *= Scalar;
        Columns[1] *= Scalar;
        Columns[2] *= Scalar;
        Columns[3] *= Scalar;
        return *this;
    }

    void Matrix4::Rotate(float Radians, const Vector3& Axis)
    {
        *this = Math::Rotate(*this, Axis, Radians);
    }

    void Matrix4::Rotate(const Vector3& EulerAngles)
    {
    	*this = Math::RotateAxisAngle(*this, EulerAngles);
    }

    void Matrix4::RotateDegrees(const Vector3& EulerAnglesDegrees)
    {
        *this = Math::RotateAxisAngleDegrees(*this, EulerAnglesDegrees);
    }

    void Matrix4::RotateDegrees(float Degrees, const Vector3& Axis)
    {
        *this = Math::RotateDegrees(*this, Axis, Degrees);
    }

    void Matrix4::Scale(float Scalar)
    {
        *this = Math::Scale(*this, Scalar);
    }

    void Matrix4::Scale(const Vector3& Scale)
    {
        *this = Math::Scale(*this, Scale);
    }

    void Matrix4::Translate(const Vector3& Translation)
    {
        *this = Math::Translate(*this, Translation);
    }
}
