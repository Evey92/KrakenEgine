#pragma once
#include <kraTexture.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11ShaderResourceView.h"

namespace kraEngineSDK {
  
  
  class Device;

  class KRA_UTILGFX_EXPORT TextureDX : 
  public Texture {

   public:
     TextureDX() = default;
     TextureDX(const TextureDX& newTex);
     ~TextureDX() {}

    void
    createTexture2D(const Device& pDevice, int height, int width);
    void
    createTexture2D(void* pDevice, int height, int width,
                    void* format, void* bindFlag, void* desc);
    bool
    createTexture2DFromFile(const Device& pDevice, std::string filename);
    void
    setTextureShaderResource(const Device* pDevice,
                             uint32 startSlot,
                             uint32 numViews);
    void
    releaseTexture();

    ID3D11Texture2D* m_pd3dTexture2D = nullptr;
    ID3D11ShaderResourceView* m_pTextureRV = nullptr;
    int m_height = 0;
    int m_width = 0;
    std::string m_missingTexture = "resources/Textures/missingChecker.png";

  };
}
