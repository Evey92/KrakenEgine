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
                         TEXTURE_ADDRESS_MODE::E addressMode);

    void
    setSamplerState(const Device& pDevice);

    ID3D11SamplerState* m_samplerState = nullptr;
  };
}
