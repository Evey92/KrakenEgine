#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDevice.h"
#include "kraTexture.h"

namespace kraEngineSDK {

  class ShaderResourceView
  {
  public:
    ShaderResourceView() = default;
    virtual 
    ~ShaderResourceView() {}

    virtual bool
    createShaderResourceView(Device* pDevice, Texture* texture) = 0;
    virtual void
    setShaderResourceView(Device* pDeviceContext) = 0;
  };
}