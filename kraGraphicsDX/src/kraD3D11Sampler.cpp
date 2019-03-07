#include <kraDevice.h>

#include "kraD3D11Sampler.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
  
  bool
  SamplerStateDX::createSamplerState(Device* pDevice) {

    DeviceDX* m_pDevice = static_cast<DeviceDX*>(pDevice);

    HRESULT hr = S_OK;

    D3D11_SAMPLER_DESC sampDesc;
    memset(&sampDesc, 0, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = m_pDevice->m_pd3dDevice->CreateSamplerState(&sampDesc, &m_samplerState);
        
    if (FAILED(hr)) {
      return false;
    }

    return true;
  }

}