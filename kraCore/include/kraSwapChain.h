#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SwapChain
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
