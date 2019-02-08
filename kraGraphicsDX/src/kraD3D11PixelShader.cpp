#include "kraD3D11PixelShader.h"

namespace kraEngineSDK {

  bool
  PixelShaderDX::compilePixelShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "ps_4_0", reinterpret_cast<void**>(m_blob));

    if (FAILED(hr))
    {
      return hr;
    }
  }

  bool
  PixelShaderDX::createPixelShader(void* pDevice) {

    ID3D11Device* m_pDevice = reinterpret_cast<ID3D11Device*>(pDevice);

    HRESULT hr = S_OK;
    hr = m_pDevice->CreatePixelShader(m_blob->GetBufferPointer(),
                                    m_blob->GetBufferSize(),
                                    NULL, &m_pPixelShader);
    if (FAILED(hr))
    {
      m_blob->Release();
      return hr;
    }
  }

  void
    PixelShaderDX::cleanShader() {
    m_blob->Release();
    m_pPixelShader->Release();
  }
}
