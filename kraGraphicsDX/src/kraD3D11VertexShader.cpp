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
  VertexShaderDX::createVertexShader(void* pDevice) {

    ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);

    HRESULT hr = S_OK;
    hr = m_pDevice->CreateVertexShader(m_blob->GetBufferPointer(),
                                     m_blob->GetBufferSize(),
                                     NULL, &m_pVertexShader);
    if (FAILED(hr))
    {
      m_blob->Release();
      return hr;
    }
  }

  void
  VertexShaderDX::cleanShader() {
    m_pVertexShader->Release();
  }
}
