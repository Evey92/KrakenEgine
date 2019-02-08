#include "kraD3D11DepthStencylView.h"

namespace kraEngineSDK {
  
  bool
  DepthStencylViewDX::createDepthStencilView(void* pDevice,
                                           void* pDepthStencil) {
    
    ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);
    DepthStencilDX* m_pDepthStencil = reinterpret_cast<DepthStencilDX*>(pDepthStencil);

    HRESULT hr = S_OK;
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    memset(&descDSV, 0, sizeof(descDSV));
    descDSV.Format = m_pDepthStencil->descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    hr = m_pDevice->CreateDepthStencilView(m_pDepthStencil->m_pd3dDepthStencil.m_pd3dTexture2D,
      &descDSV, &m_pDepthStencilView);
    if (FAILED(hr))
      return hr;

    return hr;
  }

  void
  DepthStencylViewDX::cleanDSV() {
    m_pDepthStencilView->Release();
  }

}
