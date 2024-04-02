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
    
    GUID::GUID() : m_Value(UniformDistribution(RandomEngine))
    {
    }

    GUID::operator uint64_t() const
    {
        return m_Value;
    }
}
