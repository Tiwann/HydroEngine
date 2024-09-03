#pragma once
#include "Core/NumericTypes.h"
#include "Core/Containers/String.h"

namespace Hydro
{
    enum class InputState : u8
    {
        None,
        Pressed,
        Released,
    };

    inline String InputStateToString(InputState State)
    {
        switch (State)
        {
        case InputState::None: return "None";
        case InputState::Pressed: return "Pressed";
        case InputState::Released: return "Released";
        }
        return "None";
    }
}

#include <spdlog/fmt/bundled/core.h>
#include <spdlog/fmt/bundled/format.h>
HYDRO_ENUM_FMT(Hydro::InputState, Hydro::InputStateToString);
