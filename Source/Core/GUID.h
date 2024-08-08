#pragma once

namespace Hydro
{
    class GUID
    {
    public:
        GUID();
        GUID(const GUID& Guid);
        GUID(uint64_t Low, uint64_t High);
        uint64_t* GetValues();
        std::string GetString() const;
    private:
        uint64_t m_Values[2] = {};
    };
}
