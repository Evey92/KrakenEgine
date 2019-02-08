#pragma once
#include <kraSwapChain.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT SwapChainDX : public SwapChain
  {
   public:
    SwapChainDX() = default;
    ~SwapChainDX() {}

    void
    setSwapChainDescriptor(void* g_hWnd, 
                           int width,
                           int height, void* swapDescriptor);

    IDXGISwapChain* m_pd3dSwapChain = nullptr;
  };
}
