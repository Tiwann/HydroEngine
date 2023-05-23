#include "HydroPCH.h"
#include "BinarySerializer.h"

namespace Hydro
{
    template <typename T>
    BinarySerializer<T>::BinarySerializer(String&& filepath) : Serializer(filepath)
    {
        Super::m_File = fopen(*Super::m_Filepath, "wb");
        if(!Super::m_File)
        {
            HYDRO_LOG_ERROR("[SERIALIZER] Failed to open file");
        }
    }

    
}
