#include "kraD3D11DepthStencil.h"

namespace kraEngineSDK {

  void
  DepthStencil::createDepthStencil(ID3D11Device* pDevice, int height, int width) {

    m_pd3dDepthStencil.createTexture2D(pDevice, height, width,
      DXGI_FORMAT_D24_UNORM_S8_UINT,
      D3D11_BIND_DEPTH_STENCIL, descDepth);
  }

  void
  DepthStencil::cleanDepthStencil() {
    m_pd3dDepthStencil.m_pd3dTexture2D->Release();
  }
}
