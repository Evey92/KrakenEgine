#include "kraD3D11Viewport.h"


namespace kraEngineSDK {

  void
    Viewport::createViewport(uint32 width, uint32 height,
      float TopLeftX, float TopLeftY) {
    m_pd3dviewport.Height = (float)height;
    m_pd3dviewport.Width = (float)width;
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
