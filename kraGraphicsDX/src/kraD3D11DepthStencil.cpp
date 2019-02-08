#include "kraD3D11DepthStencil.h"

namespace kraEngineSDK {

  void
  DepthStencilDX::createDepthStencil(void* pDevice, int height, int width) {

    ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);

    m_pd3dDepthStencil.createTexture2D(reinterpret_cast<void*>(m_pDevice), height, width,
      reinterpret_cast<void*>(DXGI_FORMAT_D24_UNORM_S8_UINT),
      reinterpret_cast<void*>(D3D11_BIND_DEPTH_STENCIL), reinterpret_cast<void*>(&descDepth));
  }

  void
  DepthStencilDX::cleanDepthStencil() {
    m_pd3dDepthStencil.m_pd3dTexture2D->Release();
  }
}
