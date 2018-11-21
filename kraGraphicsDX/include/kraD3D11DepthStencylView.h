#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11DepthStencil.h" 

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT DepthStencylView
  {
  public:
    DepthStencylView() = default;
    ~DepthStencylView() {};

    HRESULT
    createDepthStencilView(ID3D11Device* pDevice,
        DepthStencil* pDepthStencil) {
      HRESULT hr = S_OK;
      D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
      memset(&descDSV, 0, sizeof(descDSV));
      descDSV.Format = pDepthStencil->descDepth.Format;
      descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
      descDSV.Texture2D.MipSlice = 0;

      hr = pDevice->CreateDepthStencilView(pDepthStencil->m_pd3dDepthStencil.m_pd3dTexture2D,
        &descDSV, &m_pDepthStencilView);
      if (FAILED(hr))
        return hr;

      return hr;
    }

    void
    cleanDSV() {
      m_pDepthStencilView->Release();
    }

    ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
  };
}