#pragma once
#include <kraDepthStencil.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11Device.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  class Device;

  class KRA_UTILGFX_EXPORT DepthStencilDX : public DepthStencil
  {
   public:
     DepthStencilDX() = default;
     ~DepthStencilDX() = default;

     bool
     setDepthStencil(const Device& pDevice, uint32 height, uint32 width);
     void
     cleanDepthStencil();
     

     ID3D11Texture2D* m_pd3dDepthStencil;
  };
}
