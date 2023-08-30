#include "HydroPCH.h"
#include "DirectXDevice.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "Core/LogVerbosity.h"

namespace Hydro
{
    DirectXDevice::DirectXDevice() : RendererDevice()
    {
        HRESULT result;
        uint32_t factoryFlags = 0;

#if defined(HYDRO_DEBUG)
        ID3D12Debug* dc = nullptr;
        result = D3D12GetDebugInterface(IID_PPV_ARGS(&dc));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to get debug controller!")
        
        result = dc->QueryInterface(IID_PPV_ARGS(m_DebugController.GetAddressOf()));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to query debug controller interface!")
        m_DebugController->EnableDebugLayer();
        m_DebugController->SetEnableGPUBasedValidation(true);
        factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

        result = dc->QueryInterface(m_InfoQueue.GetAddressOf());
        HYDRO_CHECK_D3D_RESULT(result, "Failed to query info queue interface!")

        
        dc->Release();
#endif

        
        HYDRO_LOG(DirectX, Trace, "Creating DXGI Factory...");
        result = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&m_Factory));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create DirectX factory!")


        HYDRO_LOG(DirectX, Trace, "Enumerating Adapters by GPU Preference: DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE");
        result = m_Factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&m_Adapter));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to enumerate Adapters!")

        result = D3D12CreateDevice(m_Adapter.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_Device));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create D3D device!")

#if defined(HYDRO_DEBUG)
        result = m_Device->QueryInterface(m_DebugDevice.GetAddressOf());
        HYDRO_CHECK_D3D_RESULT(result, "Failed to query debug device interface!")
#endif
        
        D3D12_COMMAND_QUEUE_DESC queueDesc{};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        

        result = m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_CommandQueue.GetAddressOf()));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create command queue!")

        result = m_Device->CreateCommandAllocator(queueDesc.Type, IID_PPV_ARGS(m_CommandAllocator.GetAddressOf()));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create command allocator!")
        
        result = m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_Fence.GetAddressOf()));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create fence!")
        
        D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
        
        ID3D12PipelineState* pipeline;
        result = m_Device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipeline));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create graphics pipeline state!")
        
        result = m_Device->CreateCommandList(0, queueDesc.Type, m_CommandAllocator.Get(), pipeline, IID_PPV_ARGS(m_GraphicsCommandList.GetAddressOf()));
        HYDRO_CHECK_D3D_RESULT(result, "Failed to create command list!")
        
        
        D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier.Transition.pResource = nullptr;
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_SOURCE;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        m_GraphicsCommandList->ResourceBarrier(1, &barrier);
        
        
        m_IsReady = false;
    }

    DirectXDevice::~DirectXDevice()
    {
        m_DebugController->Release();
        m_Factory->Release();
        m_Device->Release();
    }

    void DirectXDevice::ClearDepthBuffer()
    {
            
    }

    void DirectXDevice::ClearColor(const Color& color)
    {
        
    }

    void DirectXDevice::SwapBuffers()
    {
            
    }

    void DirectXDevice::DrawIndexed()
    {
    }
}

