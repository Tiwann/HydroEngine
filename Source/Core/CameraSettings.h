#pragma once
#include "CameraProjectionType.h"
#include "Math/Vector2.h"

namespace Hydro
{
    struct CameraSettings
    {
        CameraProjectionType Projection;
        float Width, Height;
        float FieldOfView;
        float OrthoSize;
        float NearPlane, FarPlane;

        static CameraSettings DefaultPerspective;
        static CameraSettings DefaultOrthographic;

        CameraSettings& WithDimension(float Width, float Height)
        {
            this->Width = Width;
            this->Height = Height;
            return *this;
        }

        CameraSettings& WithDimensions(const Vector2& Dimensions)
        {
            this->Width = Dimensions.x;
            this->Height = Dimensions.y;
            return *this;
        }

        CameraSettings& WithFOV(float FOV)
        {
            FieldOfView = FOV;
            return *this;
        }

        CameraSettings& WithOrthoSize(float OrthographicSize)
        {
            OrthoSize = OrthographicSize;
            return *this;
        }

        CameraSettings& SetType(CameraProjectionType Type)
        {
            Projection = Type;
            return *this;
        }

        CameraSettings& WithNearFarPlanes(float Near, float Far)
        {
            NearPlane = Near;
            FarPlane = Far;
            return *this;
        }

        void SetDimensions(Vector2 Size)
        {
            Width = Size.x;
            Height = Size.y;
        }
    };    
}
