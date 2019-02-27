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
                                         int height) = 0;
    virtual void
    present(uint32 interval, uint32 flags) = 0;
  
  };
}
