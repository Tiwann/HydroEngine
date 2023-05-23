#include "HydroPCH.h"
#include "DirectXDevice.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "GLFW/glfw3native.h"



namespace Hydro
{
    DirectXDevice::DirectXDevice(): RendererDevice()
    {
        HYDRO_LOG_TRACE("Creating DXGI Factory...");
        HRESULT result = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_Factory));
        if(FAILED(result))
        {
            HYDRO_LOG_ERROR("[D3D12] Failed to create DirectX factory!");
            Application::GetCurrentApplication().RequireExit();
            return;
        }
        

        HYDRO_LOG_TRACE("Enumerating Adapters by GPU Preference: DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE");
        result = m_Factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&m_Adapter));
        if(FAILED(result))
        {
            HYDRO_LOG_ERROR("[D3D12] Failed to enumerate Adapters!");
            Application::GetCurrentApplication().RequireExit();
            return;
        }

        result = D3D12CreateDevice(m_Adapter.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_Device));
        if(FAILED(result))
        {
            HYDRO_LOG_ERROR("[D3D12] Failed to create D3D device!");
            Application::GetCurrentApplication().RequireExit();
            return;
        }
        
        
        m_IsReady = true;
    }

    DirectXDevice::~DirectXDevice()
    {
        
    }

    void DirectXDevice::ClearDepthBuffer()
    {
            
    }

    void DirectXDevice::ClearColor(Color color)
    {
        
    }

    void DirectXDevice::SwapBuffers()
    {
            
    }

    void DirectXDevice::DrawIndexed()
    {
    }
}
