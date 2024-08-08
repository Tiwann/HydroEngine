#pragma once
#include "ResourceManager.h"
#include "Audio/Sound.h"

HYDRO_DECLARE_LOG_CATEGORY_STATIC(SoundManager, "SOUND MANAGER")

namespace Hydro
{
    class SoundManager : public ResourceManager<Sound>
    {
    public:
        Ref<Sound> Load(const std::string& Name, const Path& Filepath, SoundFlags Flags);
        Ref<Sound> Load(const std::string& Name, const Path& Filepath) override;
        Ref<Sound> Retrieve(const std::string& Name) override;
    };
}
