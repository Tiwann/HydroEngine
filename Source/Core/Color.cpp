#include "Color.h"
#include "Math/Vector4.h"

namespace Hydro
{
    Color::Color()
    {
        r = g = b = 0.0f;
        a = 1.0f;
    }

    Color::Color(uint32_t color)
    : r((color >> 24 & 0xFF) / 255.0f), g((color >> 16 & 0xFF) / 255.0f), b((color >> 8 & 0xFF) / 255.0f), a((color & 0xFF) / 255.0f)
    {
    }

    Color::Color(float red, float green, float blue, float alpha)
    : r(red), g(green), b(blue), a(alpha)
    {
    }
    
    Color::operator Vector4() const
    {
        return { r, g, b, a };
    }

    Color Color::FromHSL(float hue, float saturation, float lightness, float alpha)
    {
        return 0;
    }
    
    Color Color::WithHue(float hue)
    {
        return 0;
    }

    Color Color::WithSaturation(float saturation)
    {
        return 0;
    }

    Color Color::WithLightness(float lightness)
    {
        return { r * lightness, g * lightness, b * lightness, a };
    }

    Color Color::WithOpacity(float opacity)
    {
        return { r, g, b, opacity };
    }

    Color Color::WithRed(float red)
    {
        return { red, g, b, a };
    }

    Color Color::WithGreen(float green)
    {
        return { r, green, b, a };
    }

    Color Color::WithBlue(float blue)
    {
        return { r, g, blue, a };
    }
    
    Color Color::Red        { 0xFF0000FF };
    Color Color::Green      { 0x00FF00FF };
    Color Color::Blue       { 0x0000FFFF };
    Color Color::Magenta    { 0xFF00FFFF };
    Color Color::Cyan       { 0x00FFFFFF };
    Color Color::Yellow     { 0xFFFF00FF };
    Color Color::Black      { 0x000000FF };
    Color Color::White      { 0xFFFFFFFF };
    Color Color::Orange     { 0xFF8000FF };
    Color Color::Pink       { 0xFFC0CBFF };
    Color Color::Brown      { 0x00000000 };
    Color Color::Purple     { 0x800080FF };
    Color Color::Turquoise  { 0x40E0D0FF };
    Color Color::Grey       { 0x808080FF };
}
