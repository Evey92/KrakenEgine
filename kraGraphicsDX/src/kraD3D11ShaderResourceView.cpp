#include "kraD3D11ShaderResourceView.h"


namespace kraEngineSDK {
  HRESULT
  ShaderResourceView::createShaderResourceView(ID3D11Device* pDevice, 
                                               ID3D11Texture2D* texture) {
    HRESULT hr;
    hr = pDevice->CreateShaderResourceView(texture, nullptr, &m_pTextureRV);
    
    if (FAILED(hr)) {
      throw std::exception("Failed to create Shader Resource View.");
      return hr;
    }

    return hr;
  }

  void
  ShaderResourceView::setShaderResourceView(ID3D11DeviceContext* pDeviceContext) {
    //HRESULT hr = S_OK;
    
    pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureRV);
  }

}