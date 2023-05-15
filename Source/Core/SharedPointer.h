#pragma once
#include "HydroPCH.h"

namespace Hydro
{
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    Ref<T> CreateRef(const T& object)
    {
        return std::make_shared<T>(object);
    }
}