#include "HydroPCH.h"
#include "Draw.h"

#include "Application.h"
#include "Renderer.h"

#include "shaderc/shaderc.hpp"

void Hydro::Draw::Point(const glm::vec2& Position, float Radius, const Color& Color)
{
    Renderer& Renderer = Application::GetCurrentApplication().GetRenderer();
}

void Hydro::Draw::Point(float X, float Y, float Radius, const Color& Color)
{
}
