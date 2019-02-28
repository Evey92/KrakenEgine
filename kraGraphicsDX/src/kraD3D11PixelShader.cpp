#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11PixelShader.h"
#include "kraD3D11Device.h"


namespace kraEngineSDK {

  bool
  PixelShaderDX::compilePixelShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "ps_4_0", m_blob);

    return !FAILED(hr);
  }

  bool
  PixelShaderDX::createPixelShader(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    BlobDX* myBlob = reinterpret_cast<BlobDX*>(m_blob);

    HRESULT hr = S_OK;

    hr = m_pDevice->m_pd3dDevice->CreatePixelShader(myBlob->m_blob->GetBufferPointer(),
                                                    myBlob->m_blob->GetBufferSize(),
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
    //myBlob->m_blob->Release();
    m_pPixelShader->Release();
  }

  void
  PixelShaderDX::setPixelShader(Device* pDevice) {
    
    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    m_pDevice->m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

  }

  BlobDX*
  PixelShaderDX::getBlobasDX() {
    return reinterpret_cast<BlobDX*>(m_blob);
  }

}
