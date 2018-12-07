#include "kraD3D11Device.h"


namespace kraEngineSDK {

  HRESULT
  Device::initializeDevice(HWND g_hWnd) {

    HRESULT hr = S_OK;
    RECT rc;

    GetClientRect(g_hWnd, &rc);

    m_width = rc.right - rc.left;
    m_height = rc.bottom - rc.top;

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

  void
  Device::setRenderTarget(ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV) {
    m_pImmediateContext->OMSetRenderTargets(1, &pRTV, pDSV);
  }

  void
    Device::cleanContext() {
    m_pImmediateContext->Release();
  }

  void
    Device::cleanDevice() {
    m_pd3dDevice->Release();
  }

  void
    Device::cleanSwapChain() {
    m_pSwapChain->Release();
  }

  void
    Device::cleanContextState() {
    m_pImmediateContext->ClearState();
  }
}