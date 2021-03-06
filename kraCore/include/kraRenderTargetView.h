#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDepthStencilView.h"
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
    virtual bool
    createRenderTargetView(const Device& pDevice, Texture* pTexture) = 0;
    
    virtual void
    setRenderTarget(const Device& pDevice, uint32 numViews) = 0;

    virtual void
    setRenderTarget(const Device& pDevice, const DepthStencilView& pDSV) = 0;

    virtual void
    setRenderTargets(const Device& pDevice, Vector<RenderTargetView*> renderTargets, const DepthStencilView& pDSV) = 0;

    virtual void
    cleanRTV() = 0;

    virtual void
    clearRenderTarget(const Device& pDevice, Color clearColor) = 0;

    virtual void
    clearRenderTargets(const Device& pDevice, Vector4 clearColor) = 0;

  };
}
