#pragma once
#include "kraPrerequisitesGFX.h"
#include <windows.h>

namespace kraEngineSDK {
  class Device
  {
   public:
     Device();
    ~Device();
    
    HRESULT 
    initializeDevice(HWND g_hWnd);

    uint32 m_height;
    uint32 m_width;
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
    IDXGISwapChain* m_pSwapChain = nullptr; // not anymore
  };

  HRESULT
  Device::initializeDevice(HWND g_hWnd) {

    HRESULT hr = S_OK;
    RECT rc;

    GetClientRect(g_hWnd, &rc);
    
    m_height = rc.right - rc.left;
    m_width = rc.bottom - rc.top;
    
    uint32 createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    std::vector<D3D_DRIVER_TYPE> driverTypes;
    driverTypes.push_back(D3D_DRIVER_TYPE_HARDWARE);
    driverTypes.push_back(D3D_DRIVER_TYPE_WARP);
    driverTypes.push_back(D3D_DRIVER_TYPE_REFERENCE);

    std::vector<D3D_FEATURE_LEVEL> featureLevels;
    featureLevels.push_back(D3D_FEATURE_LEVEL_11_0);
    featureLevels.push_back(D3D_FEATURE_LEVEL_10_1);
    featureLevels.push_back(D3D_FEATURE_LEVEL_10_0);

    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = m_width;
    sd.BufferDesc.Height = m_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL selectedFL;

    for (size_t driverTypeIndex = 0;
         driverTypeIndex < driverTypes.size();
         ++driverTypeIndex)
    {
      D3D_DRIVER_TYPE& dt = driverTypes[driverTypeIndex];
      hr = D3D11CreateDeviceAndSwapChain(nullptr, dt, nullptr,
                                        createDeviceFlags, &featureLevels[0],
                                        static_cast<UINT>(featureLevels.size()),
                                        D3D11_SDK_VERSION,
                                        &sd, &m_pSwapChain,
                                        &m_pd3dDevice, &selectedFL,
                                        &m_pImmediateContext);

      if (SUCCEEDED(hr)) {
        break;
      }        
    }
    if (FAILED(hr)) {
      return hr;
    }

    return hr;
  }
}