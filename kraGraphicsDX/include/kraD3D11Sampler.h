#pragma once
#include <kraSampler.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {

  class Device;

  class KRA_UTILGFX_EXPORT SamplerStateDX : public SamplerState
  {
  public:
    SamplerStateDX() = default;
    ~SamplerStateDX() {}

    bool
    createSamplerState(const Device& pDevice,
                         SAMPLER_FILTER::E filter,
                         TEXTURE_ADDRESS_MODE::E addressMode,
                         COMPARISON_FUNCTION::E compareFunction);

    void
    setSamplerState(const Device& pDevice, uint32 startSlot, uint32 numSampl);

    void 
    setComputeSamplerState(const Device& pDevice) override;


    ID3D11SamplerState* m_samplerState = nullptr;


  };
}
