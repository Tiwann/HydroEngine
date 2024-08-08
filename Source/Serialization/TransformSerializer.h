#pragma once
#include "ComponentSerializer.h"

namespace Hydro
{
    class TransformSerializer : public ComponentSerializer<Transform, Component>
    {
    public:
        explicit TransformSerializer(YAML::Emitter& Out) : ComponentSerializer(Out)
        {
        }

        bool Serialize(const Transform& Component) override;
        bool Deserialize(Transform& Component) override;
    };
}
