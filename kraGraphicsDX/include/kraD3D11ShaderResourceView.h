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
    createShaderResourceView(void* pDevice, void* texture);
    void
    setShaderResourceView(void* pDeviceContext);

    ID3D11ShaderResourceView* m_pTextureRV;
  };
}
