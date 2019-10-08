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
      createRasterizerState(const Device& pDevice,
                            FILL_MODE::E fillMode,
                            CULL_MODE::E cullMode);
    void
    setRasterizerState(const Device& pDevice);
    
    ID3D11RasterizerState* m_rasterizerState = nullptr;

  };
}
