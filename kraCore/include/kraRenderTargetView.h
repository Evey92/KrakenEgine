#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  class RenderTargetView
  {
   public:
    
    RenderTargetView() = default;
    virtual ~RenderTargetView() {}
    
    virtual bool
    createRenderTargetView(void* pDevice,
                           void* pSwapChain) = 0;

    virtual void
    cleanRTV() = 0;
  };
}
