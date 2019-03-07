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
    createRenderTargetView(const Device& pDevice) = 0;

    virtual void
    setRenderTarget(const Device& pDevice) = 0;

    virtual void
    cleanRTV() = 0;

    virtual void
    clearRenderTargetView(Device* pDevice, Vector4 clearColor) = 0;

  };
}
