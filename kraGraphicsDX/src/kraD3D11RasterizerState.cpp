#include <kraDevice.h>

#include "kraD3D11RasterizerState.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
 
  void
  RasterizerStateDX::createRasterizerState(const Device& pDevice)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);


    D3D11_RASTERIZER_DESC rasDesc;
    memset(&rasDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
 
    rasDesc.FillMode = D3D11_FILL_SOLID;
    rasDesc.CullMode = D3D11_CULL_FRONT;
    rasDesc.FrontCounterClockwise = true;
    rasDesc.AntialiasedLineEnable = true;

    m_pDevice.m_pd3dDevice->CreateRasterizerState(&rasDesc, &m_rasterizerState);
  }

  void
  RasterizerStateDX::setRasterizerState(const Device& pDevice) {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_pDevice.m_pImmediateContext->RSSetState(m_rasterizerState);
  }

}