#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11PixelShader.h"
#include "kraD3D11Device.h"


namespace kraEngineSDK {

  bool
    PixelShaderDX::compilePixelShader(const WString fileName,
                                      String entryPoint) {
    bool hr;

    hr = compileShaderFromFile(fileName,
                               entryPoint,
                               "ps_5_0");

    if (!m_pBlob)
    {
      MessageBox(NULL, "Failed to compile Pixel Shader", "Error", MB_OK);
      return false;
    }
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
    m_pPixelShader->Release();
  }

  void
    PixelShaderDX::setPixelShader(const Device& pDevice) {

    const DeviceDX& m_pDevice = static_cast<const DeviceDX&>(pDevice);
    m_pDevice.m_pImmediateContext->PSSetShader(m_pPixelShader, 0, 0);

  }

//  bool
//  PixelShaderDX::compileShaderFromFile(std::string  filename,
//                                       std::string entryPoint,
//                                       std::string shaderModel,
//                                       ID3DBlob** ppBlobOut)
//  {
//
//    bool hr;
//
//    std::ifstream VSfile(filename.c_str());
//
//    VSfile.open(filename.c_str());
//
//    std::string src;
//
//    if (!VSfile.is_open()) {
//      return false;
//    }
//
//    src = { std::istreambuf_iterator<char>(VSfile), std::istreambuf_iterator<char>() };
//    VSfile.close();
//
//
//    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//    // Setting this flag improves the shader debugging experience, but still allows 
//    // the shaders to be optimized and to run exactly the way they will run in 
//    // the release configuration of this program.
//    dwShaderFlags |= D3DCOMPILE_DEBUG;
//#endif
//
//    ID3DBlob* pErrorBlob;
//    /*hr = D3DCompileFromFile(filename, NULL, NULL, entryPoint.c_str(),
//      shaderModel.c_str(), dwShaderFlags, NULL,
//      ppBlobOut, &pErrorBlob);*/
//
//    hr = D3DCompile(src.c_str(), src.size(), filename.c_str(), 0, 0, entryPoint.c_str(), shaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG, 0, &m_pBlob, &pErrorBlob);
//
//
//    if (FAILED(hr))
//    {
//      if (pErrorBlob != NULL) {
//
//        DWORD err = GetLastError();
//
//        MessageBox(NULL, "Failed to compile Pixel Shader Blob", "Error", MB_OK);
//        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
//        pErrorBlob->Release();
//        return false;
//      }
//
//      return true;
//    }
//
//  }
}