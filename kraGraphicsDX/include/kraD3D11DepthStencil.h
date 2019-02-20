#pragma once
#include <kraDepthStencil.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  class Device;

  class KRA_UTILGFX_EXPORT DepthStencilDX : public DepthStencil
  {
   public:
     DepthStencilDX() = default;
     ~DepthStencilDX() = default;

     ID3D11Texture2D* m_pd3dDepthStencil;
  };
}
