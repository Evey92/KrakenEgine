#include <kraDevice.h>

#include "kraD3D11Sampler.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
  
  bool
  SamplerStateDX::createSamplerState(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    HRESULT hr = S_OK;

    D3D11_SAMPLER_DESC sampDesc;
    memset(&sampDesc, 0, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.MipLODBias = 0.0f;
    sampDesc.MaxAnisotropy = 1;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sampDesc.BorderColor[0] = 0;
    sampDesc.BorderColor[1] = 0;
    sampDesc.BorderColor[2] = 0;
    sampDesc.BorderColor[3] = 0;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = m_pDevice.m_pd3dDevice->CreateSamplerState(&sampDesc, &m_samplerState);
        
    if (FAILED(hr)) {
      return false;
    }

    return true;
  }

  void
  SamplerStateDX::setSamplerState(const Device& pDevice) {
    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);

    m_device.m_pImmediateContext->PSSetSamplers(0, 1, &m_samplerState);
  }

}
