#pragma once
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class kraD3D11Texture
  {
   public:
    kraD3D11Texture() = default;
    ~kraD3D11Texture();

    void
    createTexture2D();

    int m_height;
    int m_width;
    ID3D11Texture2D* m_pd3dTexture2D;
  };

  void
  kraD3D11Texture::createTexture2D() {
    m_pd3dTexture2D;
  }
}
