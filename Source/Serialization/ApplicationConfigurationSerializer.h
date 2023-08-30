#pragma once
#include "Serialization/Serializer.h"
#include "Core/ApplicationConfiguration.h"

namespace Hydro
{
    class ApplicationConfigurationSerializer : public Serializer<ApplicationConfiguration>
    {
    public:

        ApplicationConfigurationSerializer(const Path& Filepath);
        bool Serialize(const ApplicationConfiguration& Configuration) override;
        
        bool Deserialize(ApplicationConfiguration& OutConfiguration) override;

    private:
        void WriteWindow(const ApplicationConfiguration& Configuration);
        void WriteGraphics(const ApplicationConfiguration& Configuration) const;
    };
}