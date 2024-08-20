#pragma once
#include "Core/Containers/String.h"

namespace Hydro
{
    struct MenuItem
    {
        String Name;
        bool* Selected = nullptr;
        std::function<void()> Callback = nullptr;
        bool Enabled = true;
    };
}
