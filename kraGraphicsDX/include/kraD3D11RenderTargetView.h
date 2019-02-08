#pragma once
#include <kraRenderTargetView.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT RenderTargetViewDX //: public RenderTargetView
  {
    public:

    RenderTargetViewDX() = default;
    ~RenderTargetViewDX() {}

    bool
    createRenderTargetView(void* pDevice,
                           void* pSwapChain);
    void 
    cleanRTV();

    ID3D11RenderTargetView* m_pRenderTargetView;
  };
}
