#pragma once
#include "kraPrerequisitesGFX.h"
#include <windows.h>

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT Device
  {
  public:
    Device() = default;
    ~Device() {};

    HRESULT
    initializeDevice(HWND g_hWnd);
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
    IDXGISwapChain* m_pSwapChain = nullptr; // not anymore
  };
}

