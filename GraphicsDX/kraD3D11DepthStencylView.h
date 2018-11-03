#pragma once
#include "kraPrerequisitesGFX.h"

class kraD3D11DepthStencylView
{
public:
  kraD3D11DepthStencylView();
  ~kraD3D11DepthStencylView();

  HRESULT
  createDepthStencilView(ID3D11Device* pDevice, ID3D11Texture2D* pDepthStencil);

  ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
};

HRESULT
kraD3D11DepthStencylView::createDepthStencilView(ID3D11Device* pDevice,
                                                 ID3D11Texture2D* pDepthStencil) {
  HRESULT hr = S_OK;
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  memset(&descDSV, 0, sizeof(descDSV));

  //descDSV.Format = pDepthStencil->;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  
  hr = pDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &m_pDepthStencilView);
}
