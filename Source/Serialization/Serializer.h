#pragma once
#include "Core/Filesystem.h"
#include "Core/Log.h"


namespace Hydro
{
    template<typename T>
    class Serializer
    {
    public:
        explicit Serializer(String&& filepath);
        virtual ~Serializer();

        virtual bool Serialize(const T&) = 0;
        virtual bool Deserialize(T&) = 0;

    protected:
        const String m_Filepath;
        FILE* m_File{nullptr};
    };
}
