#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDepthStencil.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT DepthStencylView
  {
  public:
    
    DepthStencylView() = default;
    virtual
      ~DepthStencylView() {}

    virtual bool
    createDepthStencilView(void* pDevice,
        void* pDepthStencil) = 0;

    virtual void
    cleanDSV() = 0;

  };
}