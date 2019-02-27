#pragma once
#include <kraRenderTargetView.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {

  class Device;
  class SwapChain;

  class KRA_UTILGFX_EXPORT RenderTargetViewDX : public RenderTargetView
  {
    public:

    RenderTargetViewDX() = default;
    ~RenderTargetViewDX() {}

    bool
    createRenderTargetView(Device* pDevice);
    void 
    cleanRTV();
    void
    clearRenderTargetView(Device* pDevice, Vector4 clearColor);
    ID3D11RenderTargetView* m_pRenderTargetView;
  };
}
