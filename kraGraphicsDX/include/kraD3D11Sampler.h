#pragma once
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT SamplerState
  {
  public:
    SamplerState() = default;
    ~SamplerState() {};

    HRESULT
      createSamplerState(ID3D11Device* pDevice);

    ID3D11SamplerState* m_samplerState = nullptr;
  };
}
