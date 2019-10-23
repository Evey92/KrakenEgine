#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11VertexShader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  bool
  VertexShaderDX::compileVertexShader(const WString fileName,
                                      String entryPoint) {
    bool isCompiled = false;

    isCompiled = compileShaderFromFile(fileName.c_str(),
                               entryPoint,
                               "vs_5_0",
                               &m_pBlob);

    if (!m_pBlob)
    {
      DWORD err = GetLastError();
      MessageBox(NULL, "Failed to compile Vertex Shader", "Error", MB_OK);
      return FALSE;
    }
  }

  bool
  VertexShaderDX::createVertexShader(const Device& pDevice) {

    const DeviceDX& m_pDevice = reinterpret_cast<const DeviceDX&>(pDevice);
    HRESULT hr = S_OK;
    hr = m_pDevice.m_pd3dDevice->CreateVertexShader(m_pBlob->GetBufferPointer(),
                                                     m_pBlob->GetBufferSize(),
                                                     nullptr,
                                                     &m_pVertexShader);
    if (FAILED(hr))
    {
      m_pBlob->Release();
      return false;
    }

    else return true;
  }

  void
  VertexShaderDX::cleanShader() {
    m_pVertexShader->Release();
  }

  void
  VertexShaderDX::setVertexShader(const Device& pDevice) {
    
    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_pDevice.m_pImmediateContext->VSSetShader(m_pVertexShader, 0, 0);

  }
}
