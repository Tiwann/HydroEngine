#pragma once
#include "HydroPCH.h"

#include "Color.h"
#include "SharedPointer.h"
#include "Platform/GraphicsDevice.h"

namespace Hydro
{
    class Renderer
    {
    public:
        Renderer(GraphicsDevice* device);
        ~Renderer();
        void Clear() const;
        void Clear(Color color) const;
        void SwapBuffers() const;
        
        
    
    private:
        GraphicsDevice* m_Device;
    };
}
