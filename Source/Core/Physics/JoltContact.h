#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/ContactListener.h>

namespace JPH
{
    struct Contact
    {
        const Body* BodyA;
        const Body* BodyB;
        const ContactManifold* Manifold;
        const ContactSettings* Settings;
    };
}