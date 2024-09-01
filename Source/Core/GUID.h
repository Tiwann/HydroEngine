#pragma once
#include "Core/Types.h"
#include <string>

namespace Hydro
{
    class GUID
    {
    public:
        GUID();
        GUID(const GUID& Guid);
        GUID(uint64 Low, uint64 High);
        const uint64* GetValues() const;
        std::string GetString() const;
    private:
        uint64 m_Values[2] = {};
    };
}
