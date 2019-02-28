#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11VertexShader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  bool
  VertexShaderDX::compileVertexShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "vs_5_0", m_blob);

    if (FAILED(hr))
    {
      return hr;
    }
  }

  bool
  VertexShaderDX::createVertexShader(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    BlobDX* myBlob = reinterpret_cast<BlobDX*>(m_blob);
    HRESULT hr = S_OK;
    hr = m_pDevice->m_pd3dDevice->CreateVertexShader(myBlob->m_blob->GetBufferPointer(),
                                                     myBlob->m_blob->GetBufferSize(),
                                                     NULL, &m_pVertexShader);
    if (FAILED(hr))
    {
      myBlob->m_blob->Release();
      return false;
    }

    else return true;
  }

  void
  VertexShaderDX::cleanShader() {
    m_pVertexShader->Release();
  }

  void
  VertexShaderDX::setVertexShader(Device* pDevice) {
    
    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    m_pDevice->m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);

  }

  BlobDX*
  VertexShaderDX::getBlobasDX() {
    return reinterpret_cast<BlobDX*>(m_blob);
  }

}
