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
    compileShaderFromFile(const WString filename,
                          String entryPoint,
                          String shaderModel,
                          void* ppBlobOut) = 0;
    virtual void
    cleanShader() = 0;
  };
}