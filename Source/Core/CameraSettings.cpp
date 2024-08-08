#include "HydroPCH.h"
#include "CameraSettings.h"


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
}
