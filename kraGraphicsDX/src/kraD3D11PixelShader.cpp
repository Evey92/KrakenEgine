#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11PixelShader.h"
#include "kraD3D11Device.h"


namespace kraEngineSDK {

  bool
  PixelShaderDX::compilePixelShader(const wchar_t* fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "ps_5_0", &m_pBlob);

    return !FAILED(hr);
  }

  bool
  PixelShaderDX::createPixelShader(Device* pDevice) {

    DeviceDX* m_pDevice = reinterpret_cast<DeviceDX*>(pDevice);
 
    HRESULT hr = S_OK;

    hr = m_pDevice->m_pd3dDevice->CreatePixelShader(m_pBlob->GetBufferPointer(),
                                                    m_pBlob->GetBufferSize(),
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

  /*BlobDX*
  PixelShaderDX::getBlobasDX() {
    return reinterpret_cast<BlobDX*>(m_blob);
  }*/

  bool
    PixelShaderDX::compileShaderFromFile(const wchar_t* filename,
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
