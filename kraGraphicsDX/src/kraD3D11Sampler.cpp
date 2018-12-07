#include "kraD3D11Sampler.h"


namespace kraEngineSDK {
  HRESULT
  SamplerState::createSamplerState(ID3D11Device* pDevice) {
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
    hr = pDevice->CreateSamplerState(&sampDesc, &m_samplerState);
    
    if (FAILED(hr)) {
      return hr;
    }

    return hr;
  }

}