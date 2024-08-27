#pragma once
#include "Core/RendererBackend.h"
#include "Core/LogCategory.h"


HYDRO_DECLARE_LOG_CATEGORY_STATIC(DirectX, "D3D12");


#define HYDRO_CHECK_D3D_RESULT(HRESULT, Message) \
    if(FAILED(HRESULT)) \
    { \
        HYDRO_LOG(DirectX, Error, Message);\
        g_Application->RequireExit(); \
        m_IsReady = false; \
        return; \
    }
    
namespace Hydro
{
    class DirectXRendererBackend : public RendererBackend
    {
        template<typename T>
        using D3DRef = Microsoft::WRL::ComPtr<T>;
        
    public:
        DirectXRendererBackend();
        ~DirectXRendererBackend() override;
        
        void ClearDepthBuffer() override;
        void ClearColorBuffer(const Color& color) override;
        void SwapBuffers() override;
        
        const ID3D12Device* GetDevice() const;

    private:
        D3DRef<ID3D12InfoQueue>            m_InfoQueue{nullptr};
        D3DRef<ID3D12Debug3>               m_DebugController{nullptr};
        D3DRef<ID3D12DebugDevice2>         m_DebugDevice{nullptr};
        D3DRef<IDXGIFactory7>              m_Factory{nullptr};
        D3DRef<IDXGIAdapter4>              m_Adapter{nullptr};
        D3DRef<ID3D12Device>               m_Device{nullptr};
        D3DRef<ID3D12CommandQueue>         m_CommandQueue{nullptr};
        D3DRef<ID3D12CommandAllocator>     m_CommandAllocator{nullptr};
        D3DRef<ID3D12Fence>                m_Fence{nullptr};
        D3DRef<ID3D12GraphicsCommandList>  m_GraphicsCommandList{nullptr};
    };
}
