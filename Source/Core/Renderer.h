#pragma once
#include "Color.h"
#include "Platform/RendererDevice.h"

namespace Hydro
{
    class HYDRO_API Renderer
    {
    public:
        Renderer(RendererDevice* device);
        ~Renderer();
        void Clear() const;
        void Clear(Color color) const;
        void SwapBuffers() const;

        bool IsReady() const;
    private:
        RendererDevice* m_Device;
    };
}
