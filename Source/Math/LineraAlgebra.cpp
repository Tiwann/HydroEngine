#include "HydroPCH.h"
#include "LinearAlgebra.h"

namespace Hydro
{
    Matrix2 Math::Rotate(const Matrix2& Mat, float Radians)
    {
        const Matrix2 RotationMatrix = { { Cos(Radians), Sin(Radians) }, { -Sin(Radians), Cos(Radians) } };
        return Mat * RotationMatrix;
    }

    Matrix2 Math::RotateDegrees(const Matrix2& Mat, float Degrees)
    {
        return Rotate(Mat, Radians(Degrees));
    }
    
    Matrix2 Math::Scale(const Matrix2& Mat, const Vector2& Scale)
    {
        const Matrix2 ScaleMatrix { { Scale.x, 0.0f }, { 0.0f, Scale.x } };
        return Mat * ScaleMatrix;
    }

    Matrix2 Math::Scale(const Matrix2& Mat, float Scale)
    {
        const Matrix2 ScaleMatrix { { Scale, 0.0f }, { 0.0f, Scale }};
        return Mat * ScaleMatrix;
    }

    Matrix3 Math::Rotate(const Matrix3& Mat, const Vector3& Axis, float Radians)
    {
        const float C = Cos(Radians);
        const float S = Sin(Radians);
        
        const Matrix3 XRotationMatrix = {
            { 1, 0, 0 },
            { 0, C, S },
            { 0, -S, C },
        };
        
        const Matrix3 YRotationMatrix = {
            {  C, 0, -S },
            {  0, 1,  0 },
            {  S, 0,  C },
        };

        const Matrix3 ZRotationMatrix = {
            {  C, S, 0 },
            { -S, C, 0 },
            {  0, 0, 1 },
        };

        const Matrix3& RotMat =
            Axis == Vector3::Right ? XRotationMatrix :
            Axis == Vector3::Up ? YRotationMatrix :
            Axis == Vector3::Forward ? ZRotationMatrix : Matrix3::Identity;

        return RotMat * Mat;
    }

    Matrix3 Math::RotateDegrees(const Matrix3& Mat, const Vector3& Axis, float Degrees)
    {
        return Rotate(Mat, Axis, Radians(Degrees));
    }
    
    Matrix3 Math::Scale(const Matrix3& Mat, const Vector3& Scale)
    {
        const Matrix3 ScaleMatrix = {
            {Scale.x, 0.0f, 0.0f},
            {0.0f, Scale.y, 0.0f},
            {0.0f, 0.0f, Scale.z},
        };
        return Mat * ScaleMatrix;
    }

    Matrix3 Math::Scale(const Matrix3& Mat, float Scale)
    {
        const Matrix3 ScaleMatrix = {
            {Scale, 0.0f, 0.0f},
            {0.0f, Scale, 0.0f},
            {0.0f, 0.0f, Scale},
        };
        return Mat * ScaleMatrix;
    }

    Matrix4 Math::Rotate(const Matrix4& Mat, const Vector3& Axis, float Radians)
    {
        const float C = Cos(Radians);
        const float S = Sin(Radians);
        
        const Matrix4 XRotationMatrix = {
            { 1, 0, 0, 0 },
            { 0, C, S, 0 },
            { 0, -S, C,0 },
            { 0, 0, 0, 1 },
        };
        
        const Matrix4 YRotationMatrix = {
            {  C, 0, -S, 0 },
            {  0, 1,  0, 0 },
            {  S, 0,  C, 0 },
            {  0, 0,  0, 1 }
        };

        const Matrix4 ZRotationMatrix = {
            {  C, S, 0, 0 },
            { -S, C, 0, 0 },
            {  0, 0, 1, 0 },
            {  0, 0, 0, 1 }
        };

        const Matrix4& RotMat =
            Axis == Vector3::Right ? XRotationMatrix :
            Axis == Vector3::Up ? YRotationMatrix :
            Axis == Vector3::Forward ? ZRotationMatrix : Matrix4::Identity;

        return RotMat * Mat;
    }

    Matrix4 Math::RotateDegrees(const Matrix4& Mat, const Vector3& Axis, float Degrees)
    {
        return Rotate(Mat, Axis, Radians(Degrees));
    }

    Matrix4 Math::Scale(const Matrix4& Mat, const Vector3& Scale)
    {
        const Matrix4 ScaleMatrix = {
            {Scale.x, 0.0f, 0.0, 0.0f},
            {0.0f, Scale.y, 0.0f, 0.0f},
            {0.0f, 0.0f, Scale.z, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Mat * ScaleMatrix;
    }

    Matrix4 Math::Scale(const Matrix4& Mat, float Scale)
    {
        const Matrix4 ScaleMatrix = {
            {Scale, 0.0f, 0.0, 0.0f},
            {0.0f, Scale, 0.0f, 0.0f},
            {0.0f, 0.0f, Scale, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
        return Mat * ScaleMatrix;
    }

    Matrix4 Math::RotateAxisAngle(const Matrix4& Mat, const Vector3& EulerAnglesRadians)
    {
        Matrix4 Result = Matrix4::Identity;
        if(!IsZero(EulerAnglesRadians.x)) Result.Rotate(EulerAnglesRadians.x, Vector3::Right);
        if(!IsZero(EulerAnglesRadians.y)) Result.Rotate(EulerAnglesRadians.y, Vector3::Up);
        if(!IsZero(EulerAnglesRadians.z)) Result.Rotate(EulerAnglesRadians.z, Vector3::Forward);
        return Mat * Result;
    }

    Matrix4 Math::RotateAxisAngleDegrees(const Matrix4& Mat, const Vector3& EulerAnglesDegrees)
    {
        return RotateAxisAngle(Mat, EulerAnglesDegrees.Apply(Radians));
    }

    Matrix4 Math::Translate(const Matrix4& Mat, const Vector3& Translation)
    {
        const Vector4 Trans(Translation, 1.0f);
        Matrix4 Result(Mat);
        Result[3] = Trans;
        return Result;
    }

    Matrix4 Math::Perspective(float FOV, float AspectRatio, float Near, float Far)
    {
        const float m22 = Far / (Far - Near);
        const float m23 = -(Far * Near / (Far - Near));
        const float Scale = 1.0f / Tan(Radians(FOV / 2.0f));
        return {
                {AspectRatio * Scale, 0.0f, 0.0f, 0.0f},
                  {0.0f, Scale, 0.0f, 0.0f},
                  {0.0f, 0.0f, m22, m23},
                  {0.0f, 0.0f, 1.0f, 0.0f},
            };
    }
    
    Matrix4 Math::Orthographic(float Width, float Height, float Scale, float Near, float Far)
    {
        const float x = Scale * 2.0f / Width;
        const float y = Scale * 2.0f /  Height;
        const float z = 1.0f / (Far - Near);
        
        return {
            {x   , 0.0f, +0.0f, +0.0f},
            {0.0f, y   , +0.0f, +0.0f},
            {0.0f, 0.0f, +z   , +0.0f},
            {0.0f, 0.0f, -Near / (Far - Near), +1.0f},
        };
    }

    Vector3 Math::ForwardFromRotation(const Vector3& EulerAngles)
    {
        Matrix4 Result = Matrix4::Identity;
        Result.RotateDegrees(EulerAngles);
        return Result * Vector3::Forward;
    }

    Vector3 Math::UpFromRotation(const Vector3& EulerAngles)
    {
        Matrix4 Result = Matrix4::Identity;
        Result.RotateDegrees(EulerAngles);
        return Result * Vector3::Up;
    }

    Vector3 Math::RightFromRotation(const Vector3& EulerAngles)
    {
        Matrix4 Result = Matrix4::Identity;
        Result.RotateDegrees(EulerAngles);
        return Result * Vector3::Right;  
    }
}
