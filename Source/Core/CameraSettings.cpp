#include "HydroPCH.h"
#include "CameraSettings.h"


namespace Hydro
{
    CameraSettings CameraSettings::DefaultPerspective = {
        Perspective,
        1920, 1080,
        60.0f,
        0.0f,
        0.01f, 1000.0f
    };

    CameraSettings CameraSettings::DefaultOrthographic = {
        Perspective,
        1920, 1080,
        60.0f,
        0.0f,
        0.01f, 1000.0f
    };    
}
