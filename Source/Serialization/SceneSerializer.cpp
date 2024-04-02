#include "HydroPCH.h"
#include "SceneSerializer.h"

#include <yaml-cpp/yaml.h>

namespace Hydro
{
    SceneSerializer::SceneSerializer(const Path& Filepath) : Serializer(Filepath)
    {
    }

    bool SceneSerializer::Serialize(const Scene& Scene) 
    {
        YAML::Emitter Out;

        m_Stream << Out.c_str();
        return false;
    }

    bool SceneSerializer::Deserialize(Scene& OutScene)
    {
        return false;
    }
}
