#pragma once
#include <kraShaderResourceView.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT ShaderResourceViewDX : public ShaderResourceView 
  {
  public:
    ShaderResourceViewDX() = default;
    ~ShaderResourceViewDX() {}

    bool
    createShaderResourceView(Device* pDevice, Texture* texture);
    
    void
    setShaderResourceView(Device* pDeviceContext);

    ID3D11ShaderResourceView* m_pTextureRV;
  };
}
