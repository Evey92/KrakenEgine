#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDevice.h"
#include "kraDepthStencil.h"

namespace kraEngineSDK {
  class DepthStencylView
  {
  public:
    
    DepthStencylView() = default;
    virtual
    ~DepthStencylView() = default;

    virtual bool
    createDepthStencilView(const Device& pDevice,
        const DepthStencil& pDepthStencil) = 0;

    virtual void
    cleanDSV() = 0;

  };
}