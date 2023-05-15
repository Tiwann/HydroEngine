#pragma once
#include "HydroPCH.h"

namespace Hydro
{
    template<typename T, size_t S>
    class HYDRO_API Array
    {
    public:
        Array(const std::initializer_list<T>& list);
        Array();

        constexpr size_t Size() const;
    private:
        T m_Data[S];
    };

    
}
