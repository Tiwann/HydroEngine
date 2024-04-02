#pragma once
#include "Serializer.h"

namespace Hydro
{
    class Scene;

    class SceneSerializer : public Serializer<Scene>
    {
    public:
        SceneSerializer(const Path& Filepath);
        bool Serialize(const Scene&) override;
        bool Deserialize(Scene&) override;
    };
}
