#pragma once
#include "Core/SharedPointer.h"
#include "Math/Vector3.h"


namespace Hydro
{
    class RigidBody3D;
    
    struct Contact3D
    {
        Vector3 ImpactPoint;
        Vector3 Normal;
        Ref<RigidBody3D> Other;
    };
}
