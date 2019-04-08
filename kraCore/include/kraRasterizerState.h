#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class RasterizerState
  {
   public:
    
    RasterizerState() = default;
    virtual
    ~RasterizerState() {}

    virtual void
    createRasterizerState(const Device& pDevice) = 0;
    virtual void
    setRasterizerState(const Device& pDevice) = 0;
  };
}