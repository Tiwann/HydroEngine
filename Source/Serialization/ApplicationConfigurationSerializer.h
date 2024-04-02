#pragma once
#include "Serialization/Serializer.h"
#include "Core/ApplicationConfiguration.h"

namespace YAML
{
    class Emitter;
    class Node;
}

namespace Hydro
{
    class ApplicationConfigurationSerializer : public Serializer<ApplicationConfiguration>
    {
    public:

        ApplicationConfigurationSerializer(const Path& Filepath);
        bool Serialize(const ApplicationConfiguration& Configuration) override;
        bool Deserialize(ApplicationConfiguration& OutConfiguration) override;

    private:
        void SerializeSwapchainBufferType(YAML::Emitter& Yaml, GraphicsSettings::SwapchainBufferType SwapchainBufferType);
        void DeserializeSwapchainBufferType(YAML::Node& Yaml, GraphicsSettings::SwapchainBufferType& OutSwapchainBufferType);
    };
}
