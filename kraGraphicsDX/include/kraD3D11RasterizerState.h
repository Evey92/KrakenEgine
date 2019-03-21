#pragma once
#include <kraRasterizerState.h>
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT RasterizerStateDX : public RasterizerState
  {
  public:
    RasterizerStateDX() = default;
    ~RasterizerStateDX() {}

    void
    createRasterizerState();

    ID3D11RasterizerState* m_rasterizerState;

  };
}
