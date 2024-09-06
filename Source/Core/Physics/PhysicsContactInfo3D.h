#pragma once
#include "PhysicsContactInfo.h"

namespace Hydro
{
    class PhysicsBody3D;
    struct PhysicsContactInfo3D : PhysicsContactInfo<PhysicsBody3D>{};
}