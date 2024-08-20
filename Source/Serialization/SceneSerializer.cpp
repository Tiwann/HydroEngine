#include "HydroPCH.h"
#include "SceneSerializer.h"

#include "ComponentSerializer.h"

bool Hydro::SceneSerializer::Serialize(const Ref<Scene>& Scene, const Path& Filepath)
{
    std::ofstream Stream(Filepath, std::fstream::out);
    if(!Stream.is_open()) return false;
    std::stringstream MemoryStream;
    bool Result = SerializeMemory(Scene, MemoryStream);
    if(!Result) return false;
    Stream << MemoryStream.rdbuf();
    Stream.close();
    return true;
}

bool Hydro::SceneSerializer::Deserialize(Ref<Scene>& Scene, const Path& Filepath)
{
    return false;
}

bool Hydro::SceneSerializer::SerializeMemory(const Ref<Scene>& Scene, std::stringstream& Stream)
{
    File["Scene"] = {
        { "Name", Scene->GetName() },
        { "Guid", Scene->GetGuid().GetString() }
    };

    Scene->ForEach([this](const auto& Object)
    {
        nlohmann::json JsonGameObject{ "Game Object", {
            { "Name", Object->GetName() },
            { "Guid", Object->GetGuid().GetString() },
        } };
                
        Object->ForEach([this, &JsonGameObject](const Ref<Component>& Component)
        {
            if(const auto& Tr = Cast<Transform>(Component))
            {
                std::stringstream ss;
                TransformSerializer Serializer;
                Serializer.SerializeMemory(Tr, ss);
                JsonGameObject += nlohmann::json::parse(ss.str());
            }
        });

        File["Scene"] += JsonGameObject;
    });

    Stream.clear();
    Stream << File.dump(4);
    return true;
}

bool Hydro::SceneSerializer::DeserializeMemory(const std::stringstream& Stream, Ref<Scene>& Scene)
{
    return false;
}
