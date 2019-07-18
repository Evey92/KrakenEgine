#pragma once
#include <kraShaderResourceView.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT ShaderResourceViewDX : 
    public ShaderResourceView {
  public:
    ShaderResourceViewDX() = default;
    ~ShaderResourceViewDX() {}

    bool
    createShaderResourceView(const Device& pDevice, Texture* texture);
    
    void
    setShaderResourceView(const Device* pDeviceContext, 
                          uint32 startSlot,
                          uint32 numViews);
    void
    releaseShaderResourceView();

    ID3D11ShaderResourceView* m_pTextureRV = nullptr;
  };
}
