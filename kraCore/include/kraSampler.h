#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SamplerState
  {
  public:
    SamplerState() = default;
    virtual 
    ~SamplerState() {}

    virtual bool
    createSamplerState(Device* pDevice) = 0;

  };
}