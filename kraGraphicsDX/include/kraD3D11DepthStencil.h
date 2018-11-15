#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  class DepthStencil
  {
   public:
     void createDepthStencil(ID3D11Device* pDevice, int height, int width);
     
     
     Texture* m_pd3dDepthStencil = nullptr;
     D3D11_TEXTURE2D_DESC descDepth;
  };

  void
  DepthStencil::createDepthStencil(ID3D11Device* pDevice, int height, int width) {
    
    m_pd3dDepthStencil->createTexture2D(pDevice, height, width,
                                        DXGI_FORMAT_D24_UNORM_S8_UINT,
                                        D3D11_BIND_DEPTH_STENCIL, descDepth);
  }
}