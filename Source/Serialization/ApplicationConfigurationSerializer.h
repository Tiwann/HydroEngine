#pragma once
#include "Serialization/Serializer.h"
#include "Core/ApplicationConfiguration.h"


namespace Hydro
{
    class ApplicationConfigurationSerializer : public Serializer<ApplicationConfiguration>
    {
    public:

        ApplicationConfigurationSerializer(const String& filepath);
        bool Serialize(const ApplicationConfiguration& Configuration) override;
        
        bool Deserialize(ApplicationConfiguration& OutConfiguration) override;

    private:
        void WriteWindow(const ApplicationConfiguration& Configuration) const;
        void WriteGraphics(const ApplicationConfiguration& Configuration) const;

        bool ReadWindow(ApplicationConfiguration& OutConfiguration);
        bool ReadGraphics(ApplicationConfiguration& OutConfiguration);
    };
}