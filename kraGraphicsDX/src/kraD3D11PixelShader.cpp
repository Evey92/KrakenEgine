#include "kraD3D11PixelShader.h"

namespace kraEngineSDK {

  HRESULT
    PixelShader::compilePixelShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "ps_4_0", &m_blob);

    if (FAILED(hr))
    {
      return hr;
    }
  }

  HRESULT
    PixelShader::createPixelShader(ID3D11Device* pDevice) {

    HRESULT hr = S_OK;
    hr = pDevice->CreatePixelShader(m_blob->GetBufferPointer(),
                                    m_blob->GetBufferSize(),
                                    NULL, &m_pPixelShader);
    if (FAILED(hr))
    {
      m_blob->Release();
      return hr;
    }
  }

  void
    PixelShader::cleanShader() {
    m_blob->Release();
    m_pPixelShader->Release();
  }
}
