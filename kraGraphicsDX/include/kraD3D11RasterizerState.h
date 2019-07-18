#pragma once
#include <kraRasterizerState.h>
#include "kraPrerequisitesGFX.h"


namespace kraEngineSDK {
  class Device;

  class KRA_UTILGFX_EXPORT RasterizerStateDX : public RasterizerState
  {
  public:
    RasterizerStateDX() = default;
    ~RasterizerStateDX() {}

    void
    createRasterizerState(const Device& pDevice);
    void
    setRasterizerState(const Device& pDevice);
    
    ID3D11RasterizerState* m_rasterizerState = nullptr;

  };
}
