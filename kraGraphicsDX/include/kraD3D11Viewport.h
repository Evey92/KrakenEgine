#pragma once
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT Viewport
  {
  public:
    Viewport() = default;
    ~Viewport() {};

    void
    createViewport(float width, float height, float TopLeftX, float TopLeftY);

     void
    setViewport(ID3D11DeviceContext* pDeviceContext);
    
    float m_minDepth = 0.0f;
    float m_maxDepth = 1.0f;
    D3D11_VIEWPORT m_pd3dviewport;
  };
}
