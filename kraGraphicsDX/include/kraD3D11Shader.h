#pragma once
#include "kraD3D11GraphicsBuffer.h"
#include <d3dcompiler.h>

namespace kraEngineSDK {
  class  Shader
  {
  public:
    Shader() = default;
    ~Shader() {};

    HRESULT
    compileShaderFromFile(const wchar_t* filename,
                                  std::string entryPoint,
                                  std::string shaderModel,
                                  ID3DBlob** ppBlobOut);
    /*virtual void
    cleanShader();*/
  };
}

