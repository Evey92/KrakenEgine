#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SamplerState
  {
  public:
    SamplerState() = default;
    virtual 
    ~SamplerState() {}

    virtual bool
    createSamplerState(void* pDevice) = 0;

  };
}