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
        explicit Serializer(Path Filepath) : m_Filepath(std::move(Filepath))
        {
            m_Stream = std::fstream(m_Filepath, std::fstream::in | std::fstream::out);
        }
        
        virtual ~Serializer() { m_Stream.close(); }

        virtual bool Serialize(const T&) = 0;
        virtual bool Deserialize(T&) = 0;
        
        Serializer& operator<<(const T& Obj)
        {
            Serialize(Obj);
            return *this;
        }

        Serializer& operator>>(T& Obj)
        {
            Deserialize(Obj);
            return *this;
        }

        bool IsOpened() const { return m_Stream.is_open(); }

    protected:
        Path m_Filepath;
        std::fstream m_Stream;
    };

    template<typename T>
    class BinarySerializer : public Serializer<T>
    {
    public:
        explicit BinarySerializer(const Path& Filepath)
            : Serializer<T>(Filepath)
        {
            Serializer<T>::m_Stream = std::fstream(Serializer<T>::m_Filepath, std::fstream::in | std::fstream::out |
                std::fstream::binary);
        }
    };


}
