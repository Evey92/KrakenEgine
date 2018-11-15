#pragma once
#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class Viewport
  {
  public:
    Viewport() = default;
    ~Viewport();

    void
    createViewport(float width, float height, float TopLeftX, float TopLeftY);

     void
    setViewport(ID3D11DeviceContext* pDeviceContext);
    
    float m_minDepth = 0.0f;
    float m_maxDepth = 1.0f;
    D3D11_VIEWPORT m_pd3dviewport;
  };

  void
  Viewport::createViewport(float width, float height,
                           float TopLeftX, float TopLeftY) {
    m_pd3dviewport.Height = height;
    m_pd3dviewport.Width = width;
    m_pd3dviewport.TopLeftX = TopLeftX;
    m_pd3dviewport.TopLeftY = TopLeftY;
    m_minDepth = m_minDepth;
    m_maxDepth = m_maxDepth;
  }

  void
    Viewport::setViewport(ID3D11DeviceContext* pDeviceContext) {
    pDeviceContext->RSSetViewports(1, &m_pd3dviewport);
  }
}