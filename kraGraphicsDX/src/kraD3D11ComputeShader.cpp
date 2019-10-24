#include "kraD3D11ComputeShader.h"
#include "kraD3D11ComputeShader.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {
  bool 
  ComputeShaderDX::compileComputeShader(const WString fileName, String entryPoint)
  {
    bool hr;

    hr = compileShaderFromFile(fileName, entryPoint, "cs_5_0", reinterpret_cast<void**>(&m_pBlob));

    if (!m_pBlob)
    {
      MessageBox(NULL, "Failed to compile Compute Shader", "Error", MB_OK);
      return false;
    }
  }

  bool
  ComputeShaderDX::createComputeShader(const Device& pDevice)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    HRESULT hr = S_OK;

    hr = m_pDevice.m_pd3dDevice->CreateComputeShader(m_pBlob->GetBufferPointer(),
                                                     m_pBlob->GetBufferSize(),
                                                     NULL,
                                                     &m_pcomputeShader);

    if (FAILED(hr))
    {
      return false;
    }

    return true;
  }

  void
  ComputeShaderDX::cleanShader() {
    
    m_pcomputeShader->Release();
  }

  void 
  ComputeShaderDX::setComputeShader(const Device& pDevice)
  {
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_pDevice.m_pImmediateContext->CSSetShader(m_pcomputeShader, 0, 0);
  }

}
