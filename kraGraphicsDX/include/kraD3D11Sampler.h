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
    createSamplerState(Device* pDevice);

    ID3D11SamplerState* m_samplerState = nullptr;
  };
}
