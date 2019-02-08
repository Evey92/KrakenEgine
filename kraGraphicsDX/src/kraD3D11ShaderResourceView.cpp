#include "kraD3D11ShaderResourceView.h"


namespace kraEngineSDK {
  
  bool
  ShaderResourceViewDX::createShaderResourceView(void* pDevice, 
                                               void* texture) {

    ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);
    ID3D11Texture2D* m_texture = reinterpret_cast<ID3D11Texture2D*>(texture);

    HRESULT hr;
    hr = m_pDevice->CreateShaderResourceView(m_texture, nullptr, &m_pTextureRV);
    
    if (FAILED(hr)) {
      throw std::exception("Failed to create Shader Resource View.");
    }

    return hr;
  }

  void
  ShaderResourceViewDX::setShaderResourceView(void* pDeviceContext) {
    
    ID3D11DeviceContext* m_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(pDeviceContext);
    
    m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureRV);
  }

}