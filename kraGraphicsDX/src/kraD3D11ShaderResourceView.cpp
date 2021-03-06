#include "kraD3D11ShaderResourceView.h"
#include "kraD3D11Device.h"
#include "kraD3D11Texture.h"

namespace kraEngineSDK {
  
  bool
  ShaderResourceViewDX::createShaderResourceView( const Device& pDevice, 
                                                 Texture* texture) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    TextureDX* m_texture = static_cast<TextureDX*>(texture);

    HRESULT hr;

    D3D11_SHADER_RESOURCE_VIEW_DESC desc;
    D3D11_TEXTURE2D_DESC descTexture;

    m_texture->m_pd3dTexture2D->GetDesc(&descTexture);

    desc.Format = descTexture.Format;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MostDetailedMip = 0;
    desc.Texture2D.MipLevels = 1;

    hr = m_pDevice.m_pd3dDevice->CreateShaderResourceView(m_texture->m_pd3dTexture2D, &desc, &m_pTextureRV);
    
    if (!m_pTextureRV) {
      MessageBox(NULL, "Failed to load Shader Resource View", "Error", MB_OK);
      throw std::exception("Failed to create Shader Resource View.");
      return false;
    }

    return true;
  }

  void
  ShaderResourceViewDX::setShaderResourceView(const Device* pDevice,
                                              uint32 startSlot,
                                              uint32 numViews) {
    
    const DeviceDX* m_pDevice = static_cast<const DeviceDX*>(pDevice);

    m_pDevice->m_pImmediateContext->PSSetShaderResources(startSlot,
                                                         numViews,
                                                         &m_pTextureRV);
  }

  void
  ShaderResourceViewDX::releaseShaderResourceView() {
    m_pTextureRV->Release();
  }

}