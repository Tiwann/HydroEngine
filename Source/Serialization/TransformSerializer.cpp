#include "HydroPCH.h"
#include "TransformSerializer.h"

#include "Components/Transform.h"

namespace Hydro
{
    bool TransformSerializer::Serialize(const Transform& Component)
    {
        const Vector3& Pos = Component.GetPosition();
        const Vector3& Rot = Component.GetPosition();
        const Vector3& Scale = Component.GetPosition();

        m_Emitter << YAML::Key << "Transform" << YAML::Value;
        m_Emitter << YAML::BeginMap;
        m_Emitter << YAML::Key << "GUID" << YAML::Value << Component.GetGuid().GetString();
        
        /* Position */
        m_Emitter << "Position" << YAML::Flow;
        m_Emitter << YAML::BeginSeq << Pos.x << Pos.y << Pos.z << YAML::EndSeq;

        /* Rotation */
        m_Emitter << "Rotation" << YAML::Flow;
        m_Emitter << YAML::BeginSeq << Rot.x << Rot.y << Rot.z << YAML::EndSeq;
        
        /* Scale */
        m_Emitter << "Scale" << YAML::Flow;
        m_Emitter << YAML::BeginSeq << Scale.x << Scale.y << Scale.z << YAML::EndSeq;

        m_Emitter << YAML::EndMap;
        return true;
    }

    bool TransformSerializer::Deserialize(Transform& Component)
    {
        return false;
    }
}
