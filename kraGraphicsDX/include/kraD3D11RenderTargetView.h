#pragma once
#include <kraRenderTargetView.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {

  class Device;
  class SwapChain;
  class Texture;

  class KRA_UTILGFX_EXPORT RenderTargetViewDX : public RenderTargetView
  {
    public:

    RenderTargetViewDX() = default;
    ~RenderTargetViewDX() {}

    bool
    createRenderTargetView(const Device& pDevice);
    
    bool
    createRenderTargetView(const Device& pDevice, Texture* pTexture);
    
    void
    setRenderTarget(const Device& pDevice, uint32 numViews);
    
    void
    setRenderTarget(const Device& pDevice, const DepthStencilView& pDSV) override;
    
    void
    setRenderTargets(const Device& pDevice, Vector<RenderTargetView*> renderTargets, const DepthStencilView& pDSV);

    void 
    cleanRTV();
    
    void
    clearRenderTarget(const Device& pDevice, Color clearColor);
    
    void
    clearRenderTargets(const Device& pDevice, Vector4 clearColor);
    
    
    ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
    Vector<ID3D11RenderTargetView*> m_viewsVec;
  };
}
