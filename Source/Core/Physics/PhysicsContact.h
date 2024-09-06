#pragma once

namespace Hydro
{
    template<typename WorldType, typename BodyType, typename ContactType>
    struct PhysicsContact
    {
        WorldType* World;
        BodyType* BodyA;
        BodyType* BodyB;
        ContactType* Handle;
    };
}