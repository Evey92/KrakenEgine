#pragma once
#include <windows.h>
#include <kraDevice.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11SwapChain.h"
#include "kraD3D11DepthStencil.h"



namespace kraEngineSDK {

  class KRA_UTILGFX_EXPORT DeviceDX : public Device
  {

  public:
    DeviceDX() = default;
    ~DeviceDX() {}

    bool
    initializeDevice(void* g_hWnd);
    void
    setRenderTarget(void* pRTV, void* pDSV);
    DepthStencil
    createDepthStencil(int height, int width);
    void
    cleanDepthStencil(DepthStencil* depthStencil);
    void
    cleanContext();
    void
    cleanDevice();
    void
    cleanSwapChain();
    void
    cleanContextState();

    uint32 m_height;
    uint32 m_width;
    ID3D11Device* m_pd3dDevice = nullptr;
    ID3D11DeviceContext* m_pImmediateContext = nullptr;
    SwapChainDX* m_pSwapChain;
  };
}

