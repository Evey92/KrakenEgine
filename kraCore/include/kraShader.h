#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Shader
  {
  public:
    Shader() = default;
    virtual 
    ~Shader() {}

    virtual bool
    compileShaderFromFile(const wchar_t* filename,
                          std::string entryPoint,
                          std::string shaderModel,
                          void** ppBlobOut) = 0;
    virtual void
    cleanShader() = 0;
  };
}