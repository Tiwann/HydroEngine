#include "HydroPCH.h"
#include "RendererBackend.h"

#include "Application.h"
#include "..\Platform\PlatformRendererBackend.h"
#include "Components/Camera.h"

namespace Hydro
{
    Ref<RendererBackend> RendererBackend::Create(Application* Owner)
    {
        HYDRO_RHI_PLATFORM_RETURN(RendererBackend, Owner);
    }

    void RendererBackend::SetCullMode(CullMode Mode)
    {
        m_CullMode = Mode;
    }

    bool RendererBackend::IsReady() const
    {
        return m_IsReady;
    }

    void RendererBackend::SetCurrentCamera(const Ref<Camera>& Camera)
    {
        m_CurrentCamera = Camera;
    }

    Ref<Camera> RendererBackend::GetCurrentCamera()
    {
        return m_CurrentCamera;
    }
}

