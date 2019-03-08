#pragma once
#include <kraDepthStencilView.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {

  class DepthStencil;
 

  class KRA_UTILGFX_EXPORT DepthStencylViewDX : public DepthStencylView
  {
   public:
     DepthStencylViewDX() = default;
    ~DepthStencylViewDX() {}

    bool
    createDepthStencilView(const Device& pDevice,
                           const DepthStencil& pDepthStencil);

    void
    cleanDSV();

    void
    clearDSV(const Device& pDevice);

    ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
  };

}