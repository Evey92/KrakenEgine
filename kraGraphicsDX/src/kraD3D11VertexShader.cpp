#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11VertexShader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  bool
  VertexShaderDX::compileVertexShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "vs_5_0", &m_pBlob);

    if (FAILED(hr))
    {
      return hr;
    }
  }

  bool
  VertexShaderDX::createVertexShader(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    //BlobDX* myBlob = reinterpret_cast<BlobDX*>(m_blob);
    HRESULT hr = S_OK;
    hr = m_pDevice->m_pd3dDevice->CreateVertexShader(m_pBlob->GetBufferPointer(),
                                                     m_pBlob->GetBufferSize(),
                                                     NULL, &m_pVertexShader);
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
  VertexShaderDX::setVertexShader(Device* pDevice) {
    
    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
    m_pDevice->m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);

  }

  /*BlobDX*
  VertexShaderDX::getBlobasDX() {
    return reinterpret_cast<BlobDX*>(m_blob);
  }*/

  bool
  VertexShaderDX::compileShaderFromFile(const wchar_t* filename,
      std::string entryPoint,
      std::string shaderModel,
    ID3DBlob** ppBlobOut)
  {

    //BlobDX* m_pBlob = reinterpret_cast<BlobDX*>(ppBlobOut);

    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(filename, NULL, NULL, entryPoint.c_str(),
      shaderModel.c_str(), dwShaderFlags, NULL,
      ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
      if (pErrorBlob != NULL)
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
      if (pErrorBlob) pErrorBlob->Release();
      return hr;
    }
    if (pErrorBlob) {
      pErrorBlob->Release();
    }

    return S_OK;
  }

}
