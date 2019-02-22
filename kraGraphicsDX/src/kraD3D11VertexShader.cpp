#include <kraDevice.h>

#include "kraD3D11VertexShader.h"


namespace kraEngineSDK {

  bool
  VertexShaderDX::compileVertexShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "vs_5_0", reinterpret_cast<void**>(m_blob));

    if (FAILED(hr))
    {
      return hr;
    }
  }

  bool
  VertexShaderDX::createVertexShader(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);

    HRESULT hr = S_OK;
    hr = m_pDevice->m_pd3dDevice->CreateVertexShader(m_blob->GetBufferPointer(),
                                     m_blob->GetBufferSize(),
                                     NULL, &m_pVertexShader);
    if (FAILED(hr))
    {
      m_blob->Release();
      return false;
    }

    else return true;
  }

  void
  VertexShaderDX::cleanShader() {
    m_pVertexShader->Release();
  }
}
