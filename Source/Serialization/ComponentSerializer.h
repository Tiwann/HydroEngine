#pragma once
#include "Core/Component.h"
#include "yaml-cpp/emitter.h"

namespace Hydro
{
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    class ComponentSerializer
    {
    public:
        ComponentSerializer(YAML::Emitter& Out) : m_Emitter(Out){}
        
        virtual ~ComponentSerializer() = default;
        virtual bool Serialize(const T& Component) = 0;
        virtual bool Deserialize(T& Component) = 0;
    protected:
        YAML::Emitter& m_Emitter;
    };
}
