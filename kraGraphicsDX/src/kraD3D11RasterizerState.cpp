#include <kraDevice.h>

#include "kraD3D11RasterizerState.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
 
  void
  RasterizerStateDX::createRasterizerState(const Device& pDevice,
                                           FILL_MODE::E fillMode = FILL_MODE::E::kFILL_SOLID,
                                           CULL_MODE::E cullMode = CULL_MODE::E::kCULL_BACK) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);


    D3D11_RASTERIZER_DESC rasDesc;
    memset(&rasDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
 
    rasDesc.FillMode = static_cast<D3D11_FILL_MODE>(fillMode);
    rasDesc.CullMode = static_cast<D3D11_CULL_MODE>(cullMode);
    rasDesc.FrontCounterClockwise = true;
    rasDesc.DepthClipEnable = true;

    m_pDevice.m_pd3dDevice->CreateRasterizerState(&rasDesc, &m_rasterizerState);
  }

  void
  RasterizerStateDX::setRasterizerState(const Device& pDevice) {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    m_pDevice.m_pImmediateContext->RSSetState(m_rasterizerState);
  }

}