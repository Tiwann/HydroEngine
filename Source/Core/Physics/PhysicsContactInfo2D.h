#pragma once
#include "PhysicsContactInfo.h"

namespace Hydro
{
    class PhysicsBody2D;
    struct PhysicsContactInfo2D : PhysicsContactInfo<PhysicsBody2D>{};
}