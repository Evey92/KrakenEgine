#include <kraDevice.h>

#include "kraD3D11PixelShader.h"
#include "kraD3D11Device.h"

namespace kraEngineSDK {

  bool
  PixelShaderDX::compilePixelShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "ps_4_0", reinterpret_cast<void**>(m_blob));

    return !FAILED(hr);
  }

  bool
  PixelShaderDX::createPixelShader(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);

    HRESULT hr = S_OK;

    hr = m_pDevice->m_pd3dDevice->CreatePixelShader(m_blob->GetBufferPointer(),
                                                    m_blob->GetBufferSize(),
                                                    NULL,
                                                    &m_pPixelShader);

   

    if (FAILED(hr))
    {
      return false;
    }

    return true;
  }

  void
    PixelShaderDX::cleanShader() {
    m_blob->Release();
    m_pPixelShader->Release();
  }
}
