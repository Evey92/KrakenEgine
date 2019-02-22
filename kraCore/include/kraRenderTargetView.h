#pragma once
#include "kraPrerequisitesCore.h"
#include "kraRenderTargetView.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class Device;

  class RenderTargetView
  {
   public:
    
    RenderTargetView() = default;
    virtual ~RenderTargetView() {}
    
    virtual bool
    createRenderTargetView(Device* pDevice) = 0;

    virtual void
    cleanRTV() = 0;
  };
}
