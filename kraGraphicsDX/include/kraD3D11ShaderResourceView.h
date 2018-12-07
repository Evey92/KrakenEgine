#pragma once
#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsBuffer.h"

namespace kraEngineSDK {
  class  ShaderResourceView
  {
  public:
    ShaderResourceView() = default;
    ~ShaderResourceView() {};

    HRESULT
    createShaderResourceView(ID3D11Device* pDevice, ID3D11Texture2D* texture);
    void
    setShaderResourceView(ID3D11DeviceContext* pDeviceContext);

    ID3D11ShaderResourceView* m_pTextureRV;
  };
}
