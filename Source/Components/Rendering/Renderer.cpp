#include "HydroPCH.h"
#include "Renderer.h"

#include "Core/Application.h"
#include "Platform/PlatformRenderer.h"

namespace Hydro
{
    Renderer::Renderer(const std::string& Name = "Renderer") : Component(Name)
    {
    }

    void Renderer::OnInit()
    {
        Component::OnInit();
        m_RendererBackend = &Application::GetCurrentApplication().GetRenderer();
    }

    void Renderer::OnDestroy()
    {
        Component::OnDestroy();
    }

    void Renderer::OnEnable()
    {
        Component::OnEnable();
    }

    void Renderer::OnDisable()
    {
        Component::OnDisable();
    }

    void Renderer::OnUpdate(float Delta)
    {
        Component::OnUpdate(Delta);
    }
}
