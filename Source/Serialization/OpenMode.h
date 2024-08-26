#pragma once
#include "Core/Flags.h"

enum class OpenModeFlagBits
{
    None = 0,
    HYDRO_FLAG_BIT(Read, 1),
    HYDRO_FLAG_BIT(Write, 2),
    HYDRO_FLAG_BIT(Text, 3),
    HYDRO_FLAG_BIT(Binary, 4),
    ReadText = Read | Text,
    ReadBinary = Read | Binary,
    WriteText = Write | Text,
    WriteBinary = Write | Binary,
    ReadWriteText = Read | Write | Text,
    ReadWriteBinary = Read | Write | Binary,
};

HYDRO_DECLARE_FLAGS(OpenModeFlagBits, OpenModeFlags);