#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  class Device;
  class DepthStencil;

  class DepthStencilView
  {
  public:
    
    DepthStencilView() = default;
    virtual
    ~DepthStencilView() = default;

    virtual bool
    createDepthStencilView(const Device& pDevice,
        const DepthStencil& pDepthStencil) = 0;

    virtual void
    cleanDSV() = 0;

    virtual void
    clearDSV(const Device& pDevice) = 0;

  };
}