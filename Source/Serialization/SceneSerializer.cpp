#include "HydroPCH.h"
#include "SceneSerializer.h"

namespace Hydro
{
    SceneSerializer::SceneSerializer(std::string&& filepath) : BinarySerializer(std::move(filepath))
    {
    }

    bool SceneSerializer::Serialize(const Scene&)
    {
        return false;
    }

    bool SceneSerializer::Deserialize(Scene&)
    {
        return false;
    }
}
