#pragma once
#include <unordered_map>

namespace Hydro
{
    template<typename T, typename U>
    using Map = std::unordered_map<T, U>;
}
