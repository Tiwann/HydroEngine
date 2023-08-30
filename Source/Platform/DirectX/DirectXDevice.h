#pragma once
#include "Macros.h"
#include "Platform/RendererDevice.h"
#include "Core/LogCategory.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(DirectX, "D3D12");


#define HYDRO_CHECK_D3D_RESULT(HRESULT, Message) \
    if(FAILED(HRESULT)) \
    { \
        HYDRO_LOG(DirectX, Error, Message);\
        Application::GetCurrentApplication().RequireExit(false); \
        m_IsReady = false; \
        return; \
    }
    
namespace Hydro
{
    class HYDRO_API DirectXDevice : public RendererDevice
    {
        template<typename T>
        using Ref = Microsoft::WRL::ComPtr<T>;
        
    public:
        DirectXDevice();
        ~DirectXDevice() override;
        
        void ClearDepthBuffer() override;
        void ClearColor(const Color& color) override;
        void SwapBuffers() override;
        void DrawIndexed() override;

    private:
        Ref<ID3D12InfoQueue>            m_InfoQueue{nullptr};
        Ref<ID3D12Debug3>               m_DebugController{nullptr};
        Ref<ID3D12DebugDevice2>         m_DebugDevice{nullptr};
        Ref<IDXGIFactory7>              m_Factory{nullptr};
        Ref<IDXGIAdapter4>              m_Adapter{nullptr};
        Ref<ID3D12Device>               m_Device{nullptr};
        Ref<ID3D12CommandQueue>         m_CommandQueue{nullptr};
        Ref<ID3D12CommandAllocator>     m_CommandAllocator{nullptr};
        Ref<ID3D12Fence>                m_Fence{nullptr};
        Ref<ID3D12GraphicsCommandList>  m_GraphicsCommandList{nullptr};
    };
}
