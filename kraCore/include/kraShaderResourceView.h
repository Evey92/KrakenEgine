#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT ShaderResourceView
  {
  public:
    ShaderResourceView() = default;
    virtual 
    ~ShaderResourceView() {}

    virtual bool
    createShaderResourceView(void* pDevice, void* texture) = 0;
    virtual void
    setShaderResourceView(void* pDeviceContext) = 0;
  };
}