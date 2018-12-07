#pragma once
#include "kraD3D11GraphicsBuffer.h"

namespace kraEngineSDK {
  class SwapChain
  {
   public:
    SwapChain() = default;
    ~SwapChain() {};

    DXGI_SWAP_CHAIN_DESC setSwapChainDescriptor(HWND g_hWnd, 
                                                int width,
                                                int height);

    IDXGISwapChain* m_pd3dSwapChain = nullptr;
  };
}
