#include <kraDevice.h>

#include "kraD3D11Sampler.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
  
  bool
  SamplerStateDX::createSamplerState(const Device& pDevice,
                                     SAMPLER_FILTER::E filter ,
                                     TEXTURE_ADDRESS_MODE::E addressMode) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    HRESULT hr = S_OK;

    D3D11_SAMPLER_DESC sampDesc;
    memset(&sampDesc, 0, sizeof(sampDesc));
    sampDesc.Filter = static_cast<D3D11_FILTER>(filter);
    sampDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(addressMode);
    sampDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(addressMode);
    sampDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(addressMode);
    sampDesc.MipLODBias = 0.0f;
    sampDesc.MaxAnisotropy = (filter == D3D11_FILTER_ANISOTROPIC) ? D3D11_REQ_MAXANISOTROPY : 1;
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
  SamplerStateDX::setSamplerState(const Device& pDevice, uint32 startSlot = 0, uint32 numSampl = 1) {
    
    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);
    m_device.m_pImmediateContext->PSSetSamplers(startSlot, numSampl, &m_samplerState);
  }

  void 
  SamplerStateDX::setComputeSamplerState(const Device& pDevice)
  {

    const DeviceDX& m_device = static_cast<const DeviceDX&>(pDevice);
    m_device.m_pImmediateContext->CSSetSamplers(0, 1, &m_samplerState);

  }
}
