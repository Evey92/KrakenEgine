#include <kraDevice.h>
#include <kraDepthStencil.h>

#include "kraD3D11DepthStencylView.h"
#include "kraD3D11Device.h"
#include "kraD3D11DepthStencil.h"

namespace kraEngineSDK {
  
  bool
  DepthStencylViewDX::createDepthStencilView(const Device& pDevice,
                                           const DepthStencil& pDepthStencil) {
    
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    const DepthStencilDX& m_pDepthStencil = static_cast<const DepthStencilDX&>(pDepthStencil);

    HRESULT hr = S_OK;
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    memset(&descDSV, 0, sizeof(descDSV));
    descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    hr = m_pDevice.m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil.m_pd3dDepthStencil,
      &descDSV, &m_pDepthStencilView);
    if (FAILED(hr))
      return hr;

    return hr;
  }

  void
  DepthStencylViewDX::cleanDSV() {
    m_pDepthStencilView->Release();
  }

  void
  DepthStencylViewDX::clearDSV(const Device& pDevice) {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);
    
    m_device.m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

  }

}
