#pragma once
#include "TypeTraits.h"

namespace Hydro
{
    template<typename T, typename = EnableIfType<IsFloatingPointValue<T>>>
    constexpr T FPS(int Val) { return 1.0f / (T)Val; }
}
