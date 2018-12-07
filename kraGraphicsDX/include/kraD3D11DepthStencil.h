#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT DepthStencil
  {
   public:
     void
     createDepthStencil(ID3D11Device* pDevice, int height, int width);
     
     void
     cleanDepthStencil();
     
     Texture m_pd3dDepthStencil;
     D3D11_TEXTURE2D_DESC descDepth;
  };
}
