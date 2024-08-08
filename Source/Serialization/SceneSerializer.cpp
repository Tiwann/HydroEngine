#include "HydroPCH.h"
#include "SceneSerializer.h"

#include <yaml-cpp/yaml.h>
#include "TransformSerializer.h"
#include "Components/Transform.h"

namespace Hydro
{
    bool SceneSerializer::Serialize(const Scene& Scene)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << Scene.GetName();
        out << YAML::Key << "GameObjects" << YAML::Value;

        out << YAML::BeginMap;
        Scene.ForEach([&out, this](const auto& Object)
        {
            out << YAML::Key << "GameObject" << YAML::Value << Object->GetName();
                        
            out << YAML::Key << "GUID" << YAML::Value << Object->GetGuid().GetString();
            if(Object->HasParent()) out << YAML::Key << "Parent" << YAML::Value << Object->GetParent()->GetGuid().GetString();

            out << YAML::Key << "Components" << YAML::Value;
            out << YAML::BeginMap;
            Object->ForEach([&out, this](const Ref<Component>& Component)
            {
                if(const Ref<Transform>& Tr = Cast<Transform>(Component))
                {
                    TransformSerializer Serializer(out);
                    Serializer.Serialize(*Tr);
                }
                out << YAML::Key << YAML::Value << YAML::Newline;
            });
            out << YAML::EndMap;
        });
        out << YAML::EndMap;
        
        out << YAML::EndMap;
        m_Stream << out.c_str();
        return true;
    }

    bool SceneSerializer::Deserialize(Scene& Scene)
    {
        return true;
    }
}
