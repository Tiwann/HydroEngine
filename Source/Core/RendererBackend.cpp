#include "HydroPCH.h"
#include "RendererBackend.h"
#include "Platform/PlatformRenderer.h"

namespace Hydro
{
    Ref<RendererBackend> RendererBackend::Create()
    {
        HYDRO_RHI_PLATFORM_RETURN(RendererBackend);
    }

    bool RendererBackend::IsReady() const
    {
        return m_IsReady;
    }
}

