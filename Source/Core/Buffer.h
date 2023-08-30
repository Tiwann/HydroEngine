#pragma once
#include "Macros.h"

namespace Hydro
{
    template<typename Type>
    class HYDRO_API Buffer
    {
    public:
        Buffer(const Type* buffer, size_t count) : m_Data(buffer), m_Count(count)
        {
        }

        Type* GetData()
        {
            return m_Data;
        }
        
        const Type* GetData() const
        {
            return m_Data;
        }
        
        size_t Count() const
        {
            return m_Count;
        }
        
        size_t Size() const
        {
            return m_Count;
        }
        
    private:
        Type* m_Data;
        size_t m_Count;
    };
}
