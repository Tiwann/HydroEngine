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

        CameraSettings WithDimension(float Width, float Height) const
        {
            return { Projection, Width, Height, FieldOfView, OrthoSize, NearPlane, FarPlane };
        }

        CameraSettings WithFOV(float FOV) const
        {
            return { Projection, Width, Height, FOV, OrthoSize, NearPlane, FarPlane };
        }

        CameraSettings WithOrthoSize(float OrthographicSize) const
        {
            return { Projection, Width, Height, FieldOfView, OrthographicSize, NearPlane, FarPlane };
        }

        CameraSettings SetType(CameraProjectionType Type) const
        {
            return { Type, Width, Height, FieldOfView, OrthoSize, NearPlane, FarPlane };
        }

        CameraSettings WithNearFarPlanes(float Near, float Far) const
        {
            return { Projection, Width, Height, FieldOfView, OrthoSize, Near, Far };
        }

        void SetDimensions(Vector2 Size)
        {
            Width = Size.x;
            Height = Size.y;
        }
    };    
}
