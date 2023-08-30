#include "HydroPCH.h"
#include "BinarySerializer.h"

namespace Hydro
{
    template <typename T>
    BinarySerializer<T>::BinarySerializer(std::string&& filepath) : Serializer(filepath)
    {
        Super::m_Stream = std::fstream(Super::m_Filepath, std::ios::in | std::ios::out | std::ios::binary);
    }

    
}
