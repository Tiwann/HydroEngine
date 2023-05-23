#include "HydroPCH.h"
#include "Serializer.h"
#include "ApplicationConfigurationSerializer.h"

namespace Hydro
{
    template <typename T>
    Serializer<T>::Serializer(String&& filepath) : m_Filepath(filepath)
    {
        
    }

    template <typename T>
    Serializer<T>::~Serializer()
    {
        if(m_File) fclose(m_File);
    }
    template class Serializer<ApplicationConfiguration>;
}
