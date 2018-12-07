#include "kraD3D11VertexShader.h"


namespace kraEngineSDK {

  HRESULT
    VertexShader::compileVertexShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "vs_5_0", &m_blob);

    if (FAILED(hr))
    {
      return hr;
    }
  }

  HRESULT
    VertexShader::createVertexShader(ID3D11Device* pDevice) {

    HRESULT hr = S_OK;
    hr = pDevice->CreateVertexShader(m_blob->GetBufferPointer(), 
                                     m_blob->GetBufferSize(),
                                     NULL, &m_pVertexShader);
    if (FAILED(hr))
    {
      m_blob->Release();
      return hr;
    }
  }

  void
    VertexShader::cleanShader() {
    m_pVertexShader->Release();
  }
}
