#pragma once
#include "kraPrerequisitesCore.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class SamplerState
  {
  public:
    SamplerState() = default;
    virtual 
    ~SamplerState() {}

    virtual bool
    createSamplerState(const Device& pDevice, 
                       SAMPLER_FILTER::E filter,
                       TEXTURE_ADDRESS_MODE::E addressMode,
                       COMPARISON_FUNCTION::E compareFunction) = 0;

    virtual void
    setSamplerState(const Device& pDevice, uint32 startSlot, uint32 numSampl) = 0;

    virtual void
    setComputeSamplerState(const Device& pDevice) = 0;

  };
}