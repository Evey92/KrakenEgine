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
    createShaderResourceView(const Device& pDevice, Texture* texture) = 0;
    virtual void
    setShaderResourceView(const Device* pDevice,
                          uint32 startSlot,
                          uint32 numViews) = 0;
  };
}