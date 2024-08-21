#pragma once
#include <nlohmann/json_fwd.hpp>
#include "Core/TypeTraits.h"

namespace Hydro
{
    template<class T>
    class Serializable
    {
    public:
        virtual void to_json(nlohmann::json& OutJson, const T& InSerializable) = 0;
        virtual void from_json(const nlohmann::json& InJson, T& OutSerializable) = 0;
    };
    
}
