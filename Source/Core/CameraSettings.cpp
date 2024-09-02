﻿#include "CameraSettings.h"
#include "Math/Vector2.h"

namespace Hydro
{
    CameraSettings CameraSettings::DefaultPerspective = {
        CameraProjectionType::Perspective,
        1920, 1080,
        60.0f,
        10.0f,
        0.01f, 1000.0f
    };

    CameraSettings CameraSettings::DefaultOrthographic = {
        CameraProjectionType::Orthographic,
        1920, 1080,
        60.0f,
        50.0f,
        0.01f, 1000.0f
    };

    CameraSettings& CameraSettings::WithDimension(f32 Width, f32 Height)
    {
        this->Width = Width;
        this->Height = Height;
        return *this;
    }

    CameraSettings& CameraSettings::WithDimensions(const Vector2& Dimensions)
    {
        this->Width = Dimensions.x;
        this->Height = Dimensions.y;
        return *this;
    }

    CameraSettings& CameraSettings::WithFOV(f32 FOV)
    {
        FieldOfView = FOV;
        return *this;
    }

    CameraSettings& CameraSettings::WithOrthoSize(f32 OrthographicSize)
    {
        OrthoSize = OrthographicSize;
        return *this;
    }

    CameraSettings& CameraSettings::SetType(CameraProjectionType Type)
    {
        Projection = Type;
        return *this;
    }

    CameraSettings& CameraSettings::WithNearFarPlanes(f32 Near, f32 Far)
    {
        NearPlane = Near;
        FarPlane = Far;
        return *this;
    }

    void CameraSettings::SetDimensions(Vector2 Size)
    {
        Width = Size.x;
        Height = Size.y;
    }
}
