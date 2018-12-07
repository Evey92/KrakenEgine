#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11DepthStencil.h" 

namespace kraEngineSDK {
  class  DepthStencylView
  {
  public:
    DepthStencylView() = default;
    ~DepthStencylView() {};

    HRESULT
    createDepthStencilView(ID3D11Device* pDevice,
                           DepthStencil* pDepthStencil);

    void
    cleanDSV();

    ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
  };
}