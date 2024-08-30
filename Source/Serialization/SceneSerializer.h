#pragma once
#include "Serializer.h"
#include "Core/Scene.h"
#include <nlohmann/json.hpp>


namespace Hydro
{
    class Scene;

    class SceneSerializer : public Serializer<Ref<Scene>>
    {
    public:
        bool Serialize(const Ref<Scene>& Scene, const Path& Filepath) override;
        bool Deserialize(Ref<Scene>& Scene, const Path& Filepath) override;
        bool SerializeMemory(const Ref<Scene>& Scene, std::stringstream& Stream) override;
        bool DeserializeMemory(const std::stringstream& Stream, Ref<Scene>& Scene) override;

    protected:
        nlohmann::json File;
    };
}
