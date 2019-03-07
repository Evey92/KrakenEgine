#include "kraD3D11ShaderResourceView.h"
#include "kraD3D11Device.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  
  bool
  ShaderResourceViewDX::createShaderResourceView(Device* pDevice, 
                                                 Texture* texture) {

    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);
    TextureDX* m_texture = static_cast<TextureDX*>(texture);

    HRESULT hr;

    hr = m_pDevice->m_pd3dDevice->CreateShaderResourceView(m_texture->m_pd3dTexture2D,
                                                           nullptr, &m_pTextureRV);
    
    if (FAILED(hr)) {
      throw std::exception("Failed to create Shader Resource View.");
      return false;
    }

    return true;
  }

  void
  ShaderResourceViewDX::setShaderResourceView(Device* pDevice) {
    
    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);

    m_pDevice->m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureRV);
  }

}