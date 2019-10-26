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
    createCubeTexture(void* pDevice,
                      uint32 height,
                      uint32 width,
                      GFX_FORMAT::E format,
                      GFX_USAGE::E usage,
                      CPU_USAGE::E cpuUsage,
                      uint32 levels);
    void
    createTexture2D(void* pDevice, 
                    uint32 height,
                    uint32 width,
                    GFX_FORMAT::E format,
                    GFX_USAGE::E usage,
                    CPU_USAGE::E cpuUsage,
                    uint32 levels);


    void
    createRenderableTexture2D(const Device& pDevice, int height, int width);

    bool
    createTexture2DFromFile(const Device& device,
                            String filename,
                            GFX_FORMAT::E format,
                            GFX_USAGE::E usage,
                            CPU_USAGE::E  cpuUsage) override;

    void
    createTextureUAV(const Device& device, uint32 mipSlice) override;

    void
    setTextureShaderResource(const Device* pDevice,
                             uint32 startSlot,
                             uint32 numViews);

    void 
    setTextureComputeShaderResource(const Device* pDevice, uint32 startSlot, uint32 numViews) override;


    void
    releaseTexture();

    ID3D11Resource* m_pd3dresoruce = nullptr;
    ID3D11Texture2D* m_pd3dTexture2D = nullptr;
    ID3D11ShaderResourceView* m_pSRV = nullptr;
    ID3D11UnorderedAccessView* m_UAV = nullptr;
    int m_height = 0;
    int m_width = 0;
    bool m_isHDR = false;

  };
}
