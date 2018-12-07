#include "kraD3D11DepthStencylView.h"

namespace kraEngineSDK {
  HRESULT
  DepthStencylView::createDepthStencilView(ID3D11Device* pDevice,
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
  DepthStencylView::cleanDSV() {
    m_pDepthStencilView->Release();
  }

}
