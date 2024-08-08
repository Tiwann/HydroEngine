#include "HydroPCH.h"
#include "GUID.h"

namespace Hydro
{
    namespace
    {
        std::random_device RandomDevice;
        std::mt19937_64 RandomEngine(RandomDevice());
        std::uniform_int_distribution<uint64_t> UniformDistribution;
    }
    
    GUID::GUID()
    {
        m_Values[0] = UniformDistribution(RandomEngine);
        m_Values[1] = UniformDistribution(RandomEngine);
    }

    GUID::GUID(const GUID& Guid) : m_Values{ Guid.m_Values[0], Guid.m_Values[1] }
    {
        
    }

    GUID::GUID(const uint64_t Low, const uint64_t High) : m_Values{ Low, High }
    {
    }

    uint64_t* GUID::GetValues()
    {
        return m_Values;
    }

    /* From ChatGPT */ 
    std::string GUID::GetString() const
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        ss << std::setw(8) << (m_Values[0] >> 32) << "-";
        ss << std::setw(4) << ((m_Values[0] >> 16) & 0xFFFF) << "-";
        ss << std::setw(4) << (m_Values[0] & 0xFFFF) << "-";
        ss << std::setw(4) << ((m_Values[1] >> 48) & 0xFFFF) << "-";
        ss << std::setw(12) << (m_Values[1] & 0xFFFFFFFFFFFF);
        std::string Result = ss.str();
        std::ranges::transform(Result, Result.begin(), [](const char c) -> char { return (char)std::toupper(c); });
        return Result;
    }
}
