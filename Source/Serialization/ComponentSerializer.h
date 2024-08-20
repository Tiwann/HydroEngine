#pragma once
#include "Serializer.h"
#include "Core/Component.h"
#include <nlohmann/json.hpp>

#include "Components/Transform.h"

namespace Hydro
{
    template<typename ComponentType>
    class ComponentSerializer : public Serializer<Ref<ComponentType>>
    {
    public:
        bool Serialize(const Ref<ComponentType>& Comp, const Path& Filepath) override
        {
            return false;
        }
        
        bool Deserialize(Ref<ComponentType>& Comp, const Path& Filepath) override
        {
            return false;
        }
        
        bool SerializeMemory(const Ref<ComponentType>& Comp, std::stringstream& Stream) override
        {
            File["Component"] = {
                { "Name", Comp->GetName() },
                { "GUID", Comp->GetGuid().GetString() }
            };
            return true;
        }
        
        bool DeserializeMemory(const std::stringstream& Stream, Ref<ComponentType>&) override
        {
            return false;
        }

    protected:
        nlohmann::json File;
        
    };
    
    class TransformSerializer : public ComponentSerializer<Transform>
    {
    public:
        bool Serialize(const Ref<Transform>& Comp, const Path& Filepath) override
        {
            return false;
        }
        
        bool Deserialize(Ref<Transform>& Comp, const Path& Filepath) override
        {
            return false;
        }
        
        bool SerializeMemory(const Ref<Transform>& Comp, std::stringstream& Stream) override
        {
            ComponentSerializer::SerializeMemory(Comp, Stream);
            nlohmann::json Data{{ "Position", Comp->GetPosition() },
                        { "Rotation", Comp->GetRotation() },
                        { "Scale", Comp->GetScale() }};
            
            File.at("Component").emplace(Data);
            Stream.clear();
            Stream << File.dump(4);
            return true;
        }
        
        bool DeserializeMemory(const std::stringstream& Stream, Ref<Transform>&) override
        {
            return false;
        }
        
    };


}
