#pragma once
#include "kraPrerequisitesCore.h"
#include "kraShader.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class PixelShader : public Shader {

  public:
    PixelShader() = default;
    virtual 
    ~PixelShader() {}

    virtual bool
    compilePixelShader(const wchar_t* fileName,
                       const char* entryPoint) = 0;
    virtual bool
    createPixelShader(Device* pDevice) = 0;
    virtual void
    cleanShader() = 0;
    virtual void
    setPixelShader(Device* pDevice) = 0;
  };
}
