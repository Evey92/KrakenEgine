#pragma once
#include "kraD3D11GraphicsBuffer.h"
#include <d3dcompiler.h>

namespace kraEngineSDK {
  class Shader
  {
  public:
    Shader() = default;
    ~Shader() {};

    HRESULT compileShaderFromFile(const wchar_t* filename,
                                  std::string entryPoint,
                                  std::string shaderModel,
                                  ID3DBlob** ppBlobOut);
  };

  HRESULT
    Shader::compileShaderFromFile(const wchar_t* filename,
                                      std::string entryPoint,
                                      std::string shaderModel, 
                                      ID3DBlob** ppBlobOut)
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob = nullptr;
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
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
  }
}
