#include "HydroPCH.h"
#include "Array.h"


namespace Hydro
{
    template <typename T, size_t S>
    Array<T, S>::Array(const std::initializer_list<T>& list)
    {
        for(auto& i = list.begin(); i!= list.end(); ++i)
        {
            m_Data[i] = *i;
        }
    }

    template <typename T, size_t S>
    Array<T, S>::Array()
    {
        
    }

    template <typename T, size_t S>
    constexpr size_t Array<T, S>::Size() const
    {
        return S;
    }
}
