#pragma once
#include <kraDepthStencil.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT DepthStencilDX : public DepthStencil
  {
   public:
     DepthStencilDX() = default;
     ~DepthStencilDX() {}

     void
     createDepthStencil(void* pDevice, int height, int width);
     
     void
     cleanDepthStencil();
     
     TextureDX m_pd3dDepthStencil;
     D3D11_TEXTURE2D_DESC descDepth;
  };
}
