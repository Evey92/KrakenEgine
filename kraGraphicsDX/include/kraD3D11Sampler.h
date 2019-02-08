#pragma once
#include <kraSampler.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT SamplerStateDX : public SamplerState
  {
  public:
    SamplerStateDX() = default;
    ~SamplerStateDX() {}

    bool
    createSamplerState(void* pDevice);

    ID3D11SamplerState* m_samplerState = nullptr;
  };
}
