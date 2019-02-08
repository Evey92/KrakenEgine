#pragma once
#include "kraPrerequisitesCore.h"
#include "kraShader.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT PixelShader : public Shader {

  public:
    PixelShader() = default;
    virtual 
    ~PixelShader() {}

    virtual bool
    compilePixelShader(const wchar_t* fileName,
        const char* entryPoint) = 0;

    virtual bool
    createPixelShader(void* pDevice) = 0;

    virtual void
    cleanShader() = 0;
  };
}
