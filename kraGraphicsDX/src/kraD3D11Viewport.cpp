#include <kraDevice.h>
#include "kraD3D11Viewport.h"

#include "kraD3D11Device.h"

namespace kraEngineSDK {

  void
    ViewportDX::createViewport(uint32 width, uint32 height,
      float TopLeftX, float TopLeftY) {
    m_pd3dviewport.Height = (float)height;
    m_pd3dviewport.Width = (float)width;
    m_pd3dviewport.TopLeftX = TopLeftX;
    m_pd3dviewport.TopLeftY = TopLeftY;
    m_minDepth = m_minDepth;
    m_maxDepth = m_maxDepth;
  }

  void
    ViewportDX::setViewport(Device* pDeviceContext) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDeviceContext);

    m_pDevice->m_pImmediateContext->RSSetViewports(1, &m_pd3dviewport);
  }
}
