#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class SwapChain
  {
  public:
    SwapChain() = default;
    virtual 
    ~SwapChain() {}

    virtual void setSwapChainDescriptor(void* g_hWnd,
                                         int width,
                                         int height, void* swapDescriptor) = 0;

  };
}
