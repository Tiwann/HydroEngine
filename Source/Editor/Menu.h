#pragma once
#include "Core/Containers/String.h"
#include "Core/Containers/Function.h"

namespace Hydro
{
    struct MenuItem
    {
        String Name;
        bool* Selected = nullptr;
        Function<void()> Callback = nullptr;
        bool Enabled = true;
    };
}
