#pragma once
#include <kraViewport.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT ViewportDX : public Viewport
  {
  public:
    ViewportDX() = default;
    ~ViewportDX() {}

    void
    createViewport(uint32 width, uint32 height, float TopLeftX, float TopLeftY);

     void
    setViewport(void* pDeviceContext);
    
    float m_minDepth = 0.0f;
    float m_maxDepth = 1.0f;
    D3D11_VIEWPORT m_pd3dviewport;
  };
}
