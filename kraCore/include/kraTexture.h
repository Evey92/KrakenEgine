#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Texture
  {
   public:
     Texture() = default;
    ~Texture();

    void
    createTexture2D(void* pDevice, int height, int width,
                    void* format, void* bindFlag);
    void
      createTexture2D(void** pDevice, int height, int width,
                      void* format, void* bindFlag, D3D11_TEXTURE2D_DESC desc);
    HRESULT
    createTexture2DFromFile(void* pDevice, const char*  filename,
                            DXGI_FORMAT format, D3D11_BIND_FLAG bindFlag);

    void
    releaseTexture();

    int m_height;
    int m_width; 
    const char m_missingTexture[19] = "missingChecker.png";

    void* m_pd3dTexture2D = nullptr;
  };
}
