#include "HydroPCH.h"
#include "Serializer.h"
#include "ApplicationConfigurationSerializer.h"
#include "Core/Assertion.h"

namespace Hydro
{
    template <typename T>
    Serializer<T>::Serializer(Path Filepath) : m_Filepath(std::move(Filepath)), m_Stream(std::fstream(m_Filepath, std::ios::in | std::ios::out))
    {
        HYDRO_ASSERT(m_Stream.is_open(), "IniParser: Stream is not opened or is eof!");
    }

    template <typename T>
    Serializer<T>::~Serializer()
    {
        m_Stream.close();
    }

    template class Serializer<ApplicationConfiguration>;
}
