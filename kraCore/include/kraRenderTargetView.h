#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  class KRA_CORE_EXPORT RenderTargetView
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
