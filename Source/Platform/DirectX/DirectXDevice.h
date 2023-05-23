#pragma once
#include "HydroPCH.h"
#include "Platform/RendererDevice.h"
using Microsoft::WRL::ComPtr;

namespace Hydro
{
    class HYDRO_API DirectXDevice : public RendererDevice
    {
    public:
        DirectXDevice();
        ~DirectXDevice() override;
        
        void ClearDepthBuffer() override;
        void ClearColor(Color color) override;
        void SwapBuffers() override;
        void DrawIndexed() override;

    private:
        
        ComPtr<IDXGIFactory7>   m_Factory{nullptr};
        ComPtr<IDXGIAdapter4>   m_Adapter{nullptr};
        ComPtr<ID3D12Device>    m_Device{nullptr};
        ComPtr<IDXGISwapChain1> m_Swapchain{nullptr};
    };
}
