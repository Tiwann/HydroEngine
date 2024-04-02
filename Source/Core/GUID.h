#pragma once
#include "Macros.h"
#include <random>

namespace Hydro
{
    class GUID
    {
    public:
        GUID();

        operator uint64_t() const;
    private:
        uint64_t m_Value;
    };
}
