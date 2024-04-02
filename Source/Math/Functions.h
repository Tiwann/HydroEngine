#pragma once
#include "Vector3.h"


namespace Hydro
{
    struct Math
    {
        Math() = delete;

        static constexpr float Pi = 3.14159265359f;
        static constexpr float Tau = 2.0f * Pi;
        static constexpr float PiHalf = 0.5f * Pi;
        static constexpr float E = 2.71828182846f;
        
        static float Cos(float Val);
        static float Sin(float Val);
        static float Tan(float Val);
        static float Arccos(float Val);
        static float Arcsin(float Val);
        static float Arctan(float Val);
        static float Abs(float Value);
        static float Clamp(float Value, float Min, float Max);
        static float Lerp(float A, float B, float Alpha);
        static float Map(float Value, float MinA, float MaxA, float MinB, float MaxB);
        static float Floor(float Value);
        static float Ceil(float Value);
        static float Smoothstep(float Value, float Min, float Max);
        static float MappedSin(float Val, float Min, float Max);
        static float MappedCos(float Val, float Min, float Max);
        
        
        static bool AreSame(float Lhs, float Rhs);
        static bool IsZero(float Val);
        static float Sqrt(float Val);
        static float Pow(float Val, float Exp);
        static float Radians(float Degrees);
        static float Degrees(float Radians);
        
        static class Matrix2 Rotate(const Matrix2& Mat, float Radians);
        static Matrix2 RotateDegrees(const Matrix2& Mat, float Degrees);
        static Matrix2 Scale(const Matrix2& Mat, const class Vector2& Scale);
        static Matrix2 Scale(const Matrix2& Mat, float Scale);

        static class Matrix3 Rotate(const Matrix3& Mat, const class Vector3& Axis, float Radians);
        static Matrix3 RotateDegrees(const Matrix3& Mat, const Vector3& Axis, float Degrees);
        static Matrix3 Scale(const Matrix3& Mat, const Vector3& Scale);
        static Matrix3 Scale(const Matrix3& Mat, float Scale);
        
        static class Matrix4 Rotate(const Matrix4& Mat, const Vector3& Axis, float Radians); 
        static Matrix4 RotateDegrees(const Matrix4& Mat, const Vector3& Axis, float Degrees);
        static Matrix4 Scale(const Matrix4& Mat, const Vector3& Scale);
        static Matrix4 Scale(const Matrix4& Mat, float Scale);
        static Matrix4 RotateAxisAngle(const Matrix4& Mat, const Vector3& EulerAnglesRadians);
        static Matrix4 RotateAxisAngleDegrees(const Matrix4& Mat, const Vector3& EulerAnglesDegrees);

        static float Distance(const Vector2& VecA, const Vector2& VecB);
        static float Distance(const Vector3& VecA, const Vector3& VecB);
        
        static Matrix4 Perspective(float FOV, float AspectRatio, float Near, float Far);
        static Matrix4 Orthographic(float Width, float Height, float Scale, float Near, float Far);
        static Matrix4 Translate(const Matrix4& Mat, const Vector3& Translation);


        static Vector3 ForwardFromRotation(const Vector3& EulerAngles);
        static Vector3 UpFromRotation(const Vector3& EulerAngles);
        static Vector3 RightFromRotation(const Vector3& EulerAngles);
    };
}
