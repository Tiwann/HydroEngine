#pragma once
#include "Serialization/Serializer.h"
#include "Core/ApplicationConfiguration.h"


namespace Hydro
{
    class ApplicationConfigurationSerializer : public Serializer<ApplicationConfiguration>
    {
    public:
        bool Serialize(const ApplicationConfiguration& Configuration, const Path& Filepath) override;
        bool Deserialize(ApplicationConfiguration& OutConfiguration, const Path& Filepath) override;
        bool SerializeMemory(const ApplicationConfiguration& Configuration, std::stringstream& OutStream) override;
        bool DeserializeMemory(const std::stringstream& Stream, ApplicationConfiguration& OutConfiguration) override;
    };
}
