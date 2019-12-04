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
      createRasterizerState(const Device& pDevice,
        bool depthClipEnable,
        FILL_MODE::E fillMode,
        CULL_MODE::E cullMode) = 0;
    virtual void
    setRasterizerState(const Device& pDevice) = 0;
  };
}