#include "HydroPCH.h"
#include "MeshRenderer.h"

#include "Core/Application.h"
#include "Core/RendererBackend.h"

namespace Hydro
{
    MeshRenderer::MeshRenderer() : Renderer("MeshRenderer")
    {
    }

    bool MeshRenderer::LoadMesh(const Path& Filepath)
    {
        return false;
    }

    void MeshRenderer::OnInit()
    {
        Renderer::OnInit();
    }

    void MeshRenderer::OnDestroy()
    {
        Renderer::OnDestroy();
    }

    void MeshRenderer::OnEnable()
    {
        Renderer::OnEnable();
    }

    void MeshRenderer::OnDisable()
    {
        Renderer::OnDisable();
    }

    void MeshRenderer::OnUpdate(float Delta)
    {
        Renderer::OnUpdate(Delta);
        const Application& App = Application::GetCurrentApplication();
        const RendererBackend& Renderer = App.GetRenderer();
    }
}
