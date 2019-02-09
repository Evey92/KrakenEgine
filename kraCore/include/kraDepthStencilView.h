#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDepthStencil.h"

namespace kraEngineSDK {
  class DepthStencylView
  {
  public:
    
    DepthStencylView() = default;
    virtual
    ~DepthStencylView() = default;

    virtual bool
    createDepthStencilView(void* pDevice,
        void* pDepthStencil) = 0;

    virtual void
    cleanDSV() = 0;

  };
}