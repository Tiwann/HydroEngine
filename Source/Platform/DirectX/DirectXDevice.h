#pragma once
#include "HydroPCH.h"
#include "Platform/GraphicsDevice.h"

namespace Hydro
{
    class HYDRO_API DirectXDevice : public GraphicsDevice
    {
    public:
        DirectXDevice(Application& application) : GraphicsDevice(application)
        {
            ID3D12Device* device;
            HRESULT result = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&device));
            if(FAILED(result))
            {
                throw std::runtime_error("Failed to create DirectX device!");
            }
            m_Handle = (Handle)device;
        }

        void ClearDepthBuffer() override
        {
            
        }

        void ClearColor(Color color) override
        {
            
        }
        
        void SwapBuffers() override
        {
            
        }
    };
}
