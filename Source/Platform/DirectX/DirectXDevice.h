#pragma once
#include "HydroPCH.h"
#include "Platform/GraphicsDevice.h"

namespace Hydro
{
    class HYDRO_API DirectXDevice : public GraphicsDevice
    {
    public:
        DirectXDevice() : GraphicsDevice()
        {
            HYDRO_CREATE_DX_DEVICE(Device);
            HRESULT result = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&Device));
            if(FAILED(result))
            {
                throw std::runtime_error("Failed to create DirectX device!");
            }
            HYDRO_STORE_DEVICE_HANDLE(Device);
        }

        void ClearDepthBuffer() override
        {
            HYDRO_RETRIEVE_DX_DEVICE_HANDLE(Device);
        }

        void ClearColor(Color color) override
        {
            
        }
        
        void SwapBuffers() override
        {
            
        }
    };
}
