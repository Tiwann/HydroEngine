#pragma once
#include "Core/Component.h"
#include "Core/SharedPointer.h"

namespace Hydro
{
    class Renderer : public Component
    {
    public:
        Renderer(const std::string& Name);

        void OnInit() override;
        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnUpdate(float Delta) override;
    
        class RendererBackend* m_RendererBackend;
    };
}
