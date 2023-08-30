#pragma once
#include "Core/Log.h"
#include <fstream>

#include "Core/Filesystem.h"

namespace Hydro
{
    template<typename T>
    class Serializer
    {
    public:
        explicit Serializer(Path Filepath);
        virtual ~Serializer();

        virtual bool Serialize(const T&) = 0;
        virtual bool Deserialize(T&) = 0;

    protected:
        Path m_Filepath;
        std::fstream m_Stream;
    };
}
