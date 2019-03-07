#pragma once
#include "kraPrerequisitesCore.h"
#include "kraShader.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class PixelShader {

  public:
    PixelShader() = default;
    virtual 
    ~PixelShader() {}

    virtual bool
    compilePixelShader(std::string fileName,
                       const char* entryPoint) = 0;
    virtual bool
    createPixelShader(const Device& pDevice) = 0;
    virtual void
    cleanShader() = 0;
    virtual void
    setPixelShader(const Device& pDevice) = 0;
  };
}
