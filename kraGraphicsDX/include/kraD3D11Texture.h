#pragma once
#include <kraTexture.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  
  
  class Device;

  class KRA_UTILGFX_EXPORT TextureDX : 
  public Texture {

   public:
     TextureDX() = default;
     ~TextureDX() {}

    void
    createTexture2D(const Device& pDevice, int height, int width);
    void
    createTexture2D(void* pDevice, int height, int width,
                    void* format, void* bindFlag, void* desc);
    bool
    createTexture2DFromFile(const Device&, std::string filename);

    void
    releaseTexture();

    int m_height;
    int m_width; 
    std::string m_missingTexture = "missingChecker.png";

    //ID3D11Texture1D* m_pd3dTexture1D = nullptr;
    ID3D11Texture2D* m_pd3dTexture2D = nullptr;
    //ID3D11Texture3D* m_pd3dTexture3D = nullptr;
  };
}
