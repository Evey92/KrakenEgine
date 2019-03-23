#include <kraDevice.h>
#include <kraBlob.h>

#include "kraD3D11VertexShader.h"
#include "kraD3D11Blob.h"

namespace kraEngineSDK {

  bool
  VertexShaderDX::compileVertexShader(std::string fileName,
      const char* entryPoint) {
    HRESULT hr = S_OK;

    hr = compileShaderFromFile(fileName, entryPoint, "vs_5_0");

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

  bool
  VertexShaderDX::compileShaderFromFile(std::string filename,
      std::string entryPoint,
      std::string shaderModel)
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

    ID3DBlob* pErrorBlob = nullptr;
    /*hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, entryPoint.c_str(),
      shaderModel.c_str(), dwShaderFlags, NULL,
      ppBlobOut, &pErrorBlob);*/

    hr = D3DCompile(src.c_str(), src.size(), filename.c_str(), 0, 0, entryPoint.c_str(), shaderModel.c_str(), D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG, 0, &m_pBlob, &pErrorBlob);


    if (FAILED(hr))
    {
      if (pErrorBlob != NULL) {
        DWORD err = GetLastError();
        MessageBox(NULL, "Failed to compile Vertex Shader Blob", "Error", MB_OK);
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        pErrorBlob->Release();
        return false;
      }
    }

    return true;

  }

}
