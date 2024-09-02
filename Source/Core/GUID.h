#pragma once
#include "Core/NumericTypes.h"
#include <string>

namespace Hydro
{
    class GUID
    {
    public:
        GUID();
        GUID(const GUID& Guid);
        GUID(u64 Low, u64 High);
        const u64* GetValues() const;
        std::string GetString() const;
    private:
        u64 m_Values[2] = {};
    };
}
