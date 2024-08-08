#pragma once
#include "imgui/imgui.h"

namespace Hydro
{
    enum FontNames
    {
        // Open Sans
        OpenSans_Regular,
        OpenSans_Italic,
        OpenSans_Bold,
        OpenSans_SemiBold,
        OpenSans_ExtraBold,

        // Jetbrains Mono
        JetBrainsMono_Regular,
        JetBrainsMono_Italic,
        JetBrainsMono_Bold,
        JetBrainsMono_SemiBold,
        JetBrainsMono_ExtraBold,

        NumFonts
    };
    
    inline const char* FontsPaths[NumFonts]
    {
        // Open Sans
        "Engine/Assets/Fonts/OpenSans/OpenSans-Regular.ttf",
        "Engine/Assets/Fonts/OpenSans/OpenSans-Italic.ttf",
        "Engine/Assets/Fonts/OpenSans/OpenSans-Bold.ttf",
        "Engine/Assets/Fonts/OpenSans/OpenSans-SemiBold.ttf",
        "Engine/Assets/Fonts/OpenSans/OpenSans-ExtraBold.ttf",

        // JetBrainsMono
        "Engine/Assets/Fonts/JetBrainsMono/JetBrainsMono-Regular.ttf",
        "Engine/Assets/Fonts/JetBrainsMono/JetBrainsMono-Italic.ttf",
        "Engine/Assets/Fonts/JetBrainsMono/JetBrainsMono-Bold.ttf",
        "Engine/Assets/Fonts/JetBrainsMono/JetBrainsMono-SemiBold.ttf",
        "Engine/Assets/Fonts/JetBrainsMono/JetBrainsMono-ExtraBold.ttf",
    };

    inline ImFont* Fonts[NumFonts];
}