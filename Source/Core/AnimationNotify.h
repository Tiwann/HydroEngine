#pragma once
#include "MulticastDelegate.h"
#include "Containers/String.h"
#include "NumericTypes.h"

namespace Hydro
{
    struct AnimationNotify
    {
        String Name;
        u32 Frame;
        MulticastDelegate<void()> Event;
    };
}