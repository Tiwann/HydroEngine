#pragma once
#include <string>

namespace Hydro
{
    enum class SoundFormat
    {
        None,
        PCM8,
        PCM16,
        PCM24,
        PCM32,
        PCMFloat,
        BitStream
    };

    inline std::string SoundFormatToString(SoundFormat Format)
    {
        switch (Format)
        {
        case SoundFormat::None: return "None";
        case SoundFormat::PCM8: return "PCM8";
        case SoundFormat::PCM16: return "PCM16";
        case SoundFormat::PCM24: return "PCM24";
        case SoundFormat::PCM32: return "PCM32";
        case SoundFormat::PCMFloat: return "PCM Float";
        case SoundFormat::BitStream: return "Bit Stream";
        }
        return "None";
    }
}
