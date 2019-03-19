#include <kraDevice.h>

#include "kraD3D11DepthStencil.h"

namespace kraEngineSDK {
  bool
  DepthStencilDX::setDepthStencil(const Device& pDevice, uint32 height, uint32 width) {
    
    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    D3D11_TEXTURE2D_DESC descTexture;
    memset(&descTexture, 0, sizeof(descTexture));
    descTexture.Height = height;
    descTexture.Width = width;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initBuffer;
    memset(&initBuffer, 0, sizeof(initBuffer));

    m_device.m_pd3dDevice->CreateTexture2D(&descTexture, nullptr, &m_pd3dDepthStencil);

    if (!m_pd3dDepthStencil)
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to set the Depth Stencil", "Error", MB_OK);
      //std::cout << "No se pudo crear depth sctencil";
      return false;
    }
    return true;
  }

  void
  DepthStencilDX::cleanDepthStencil() {
    m_pd3dDepthStencil->Release();
  }
}
