#pragma once
#include "kraPrerequisitesGFX.h"


namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT RenderTargetView
  {
  public:
    RenderTargetView() = default;
    ~RenderTargetView() {};

    HRESULT
    createRenderTargetView(ID3D11Device* pDevice,
                           IDXGISwapChain* pSwapChain);
    void 
    cleanRTV();

    ID3D11RenderTargetView* m_pRenderTargetView;
  };
}
