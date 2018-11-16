#pragma once
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT Texture
  {
   public:
     Texture() = default;
    ~Texture() {};

    void
    createTexture2D(ID3D11Device* pDevice, int height, int width,
                    DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag);
    void
      createTexture2D(ID3D11Device* pDevice, int height, int width,
        DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag, D3D11_TEXTURE2D_DESC desc);

    void
    releaseTexture();

    int m_height;
    int m_width;
    ID3D11Texture2D* m_pd3dTexture2D = nullptr;
  };
}
