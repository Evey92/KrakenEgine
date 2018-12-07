#pragma once
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class Texture
  {
   public:
     Texture() = default;
    ~Texture();

    void
    createTexture2D(ID3D11Device* pDevice, int height, int width,
                    DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag);
    void
      createTexture2D(ID3D11Device* pDevice, int height, int width,
                      DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag, D3D11_TEXTURE2D_DESC desc);
    HRESULT
    createTexture2DFromFile(ID3D11Device* pDevice, const char*  filename,
                            DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag);

    void
    releaseTexture();

    int m_height;
    int m_width; 
    const char m_missingTexture[19] = "missingChecker.png";

    ID3D11Texture2D* m_pd3dTexture2D = nullptr;
  };
}
