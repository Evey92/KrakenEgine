#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11PixelShader.h"
#include "kraD3D11Device.h"


namespace kraEngineSDK {

  bool
    PixelShaderDX::compilePixelShader(std::string fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "ps_4_0", &m_pBlob);

    return !FAILED(hr);
  }

  bool
    PixelShaderDX::createPixelShader(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);

    HRESULT hr = S_OK;

    hr = m_pDevice.m_pd3dDevice->CreatePixelShader(m_pBlob->GetBufferPointer(),
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
    PixelShaderDX::setPixelShader(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_pDevice.m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

  }

  /*BlobDX*
  PixelShaderDX::getBlobasDX() {
    return reinterpret_cast<BlobDX*>(m_blob);
  }*/

  bool
    PixelShaderDX::compileShaderFromFile(std::string  filename,
      std::string entryPoint,
      std::string shaderModel,
      ID3DBlob** ppBlobOut)
  {

    HRESULT hr = S_OK;

    std::ifstream VSfile(filename.c_str());

    VSfile.open(filename.c_str());

    std::string src;

    if (!VSfile.is_open()) {
      return false;
    }

    src = { std::istreambuf_iterator<char>(VSfile), std::istreambuf_iterator<char>() };
    VSfile.close();


    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    /*hr = D3DCompileFromFile(filename, NULL, NULL, entryPoint.c_str(),
      shaderModel.c_str(), dwShaderFlags, NULL,
      ppBlobOut, &pErrorBlob);*/

    hr = D3DCompile(src.c_str(), src.size(), filename.c_str(), 0, 0, entryPoint.c_str(), shaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_pBlob, &pErrorBlob);


    if (FAILED(hr))
    {
      if (pErrorBlob != NULL) {
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        return false;
      }

      if (pErrorBlob) {
        pErrorBlob->Release();
        return false;
      }
      if (pErrorBlob) {
        pErrorBlob->Release();
      }

      return true;
    }

  }
}