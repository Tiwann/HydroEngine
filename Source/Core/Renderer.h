#pragma once
#include "Macros.h"

namespace Hydro
{
    class Color;
    class RendererDevice;
    
    class HYDRO_API Renderer
    {
    public:
        Renderer(RendererDevice* device);
        ~Renderer();
        void Clear() const;
        void Clear(const Color& color) const;
        void SwapBuffers() const;

        bool IsReady() const;
    private:
        RendererDevice* m_Device;
    };
}
