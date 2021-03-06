#pragma once
#include <kraDepthStencilView.h>
#include <kraDevice.h>
#include <kraDepthStencil.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {

  class DepthStencylView;
  class DepthStencil;
  class Device;

  class KRA_UTILGFX_EXPORT DepthStencilViewDX : public DepthStencilView
  {
   public:
     DepthStencilViewDX() = default;
    ~DepthStencilViewDX() {}

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