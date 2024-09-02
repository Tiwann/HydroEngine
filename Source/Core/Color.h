#pragma once
#include "Core/NumericTypes.h"

namespace Hydro
{
    class Vector4;

    class Color
    {
    public:
        f32 r{0.0f}, g{0.0f}, b{0.0f}, a{0.0f};

        Color();
        Color(u32 color);
        Color(f32 red, f32 green, f32 blue, f32 alpha);

        operator Vector4() const;

        static Color FromHSL(f32 hue, f32 saturation, f32 lightness, f32 alpha);
        
        Color WithHue(f32 hue);
        Color WithSaturation(f32 saturation);
        Color WithLightness(f32 lightness);
        Color WithOpacity(f32 opacity);
        Color WithRed(f32 red);
        Color WithGreen(f32 green);
        Color WithBlue(f32 blue);

        static Color Red;
        static Color Green;
        static Color Blue;
        static Color Magenta;
        static Color Cyan;
        static Color Yellow;
        static Color Black;
        static Color White;
        static Color Orange;
        static Color Pink;
        static Color Brown;
        static Color Purple;
        static Color Turquoise;
        static Color Grey;
    };
}
