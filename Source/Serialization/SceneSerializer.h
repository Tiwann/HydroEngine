#pragma once
#include "Serializer.h"
#include "Core/Scene.h"

#include "yaml-cpp/emitter.h"

namespace Hydro
{
    class SceneSerializer : public Serializer<Scene>
    {
    public:
        explicit SceneSerializer(const Path& Filepath)
            : Serializer(Filepath)
        {
        }

        bool Serialize(const Scene& Scene) override;
        bool Deserialize(Scene& Scene) override;

    private:
        template<typename Key, typename Value>
        void WritePair(YAML::Emitter& Out, const Key& key, const Value& value)
        {
            Out << YAML::Key << key << YAML::Value << value;
        }
    };
}
