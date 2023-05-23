#include "HydroPCH.h"
#include "Time.h"

namespace Hydro
{
    float Time::m_Time{0.0f};
    
    float Time::GetTime()
    {
        return m_Time;
    }
}
