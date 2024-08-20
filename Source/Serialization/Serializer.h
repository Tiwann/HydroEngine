#pragma once
#include "Core/Log.h"
#include "Core/Filesystem.h"

namespace Hydro
{
    
    template<typename T>
    class Serializer
    {
    public:
        Serializer () = default;
        
        virtual ~Serializer() = default;
        
        virtual bool Serialize(const T&, const Path& Filepath) = 0;
        virtual bool Deserialize(T&, const Path& Filepath) = 0;
        virtual bool SerializeMemory(const T&, std::stringstream& Stream) = 0;
        virtual bool DeserializeMemory(const std::stringstream& Stream, T&) = 0;
    };
}
