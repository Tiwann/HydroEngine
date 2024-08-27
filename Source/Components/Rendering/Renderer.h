#pragma once
#include "Core/Component.h"

namespace Hydro
{
    class RendererBackend;
    
    class Renderer : public Component
    {
    public:
        Renderer(Entity* Owner, const std::string& Name = "Renderer") : Component(Owner, Name){}
    };
}
