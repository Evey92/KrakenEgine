#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class Blob;

  class Shader
  {
  public:
    Shader() = default;
    virtual 
    ~Shader() {}

    virtual bool
    compileShaderFromFile(const wchar_t* filename,
                          std::string entryPoint,
                          std::string shaderModel,
                          Blob* ppBlobOut) = 0;
    virtual void
    cleanShader() = 0;
  };
}