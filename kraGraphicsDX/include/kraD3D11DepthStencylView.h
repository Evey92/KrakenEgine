#pragma once
#include <kraDepthStencilView.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11DepthStencil.h" 

namespace kraEngineSDK {
  
  class KRA_UTILGFX_EXPORT DepthStencylViewDX : public DepthStencylView
  {
   public:
     DepthStencylViewDX() = default;
    ~DepthStencylViewDX() {}

    bool
    createDepthStencilView(Device* pDevice,
                           DepthStencil* pDepthStencil);

    void
    cleanDSV();

    ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
  };

}