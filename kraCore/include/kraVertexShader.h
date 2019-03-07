#pragma once
#include "kraPrerequisitesCore.h"
#include "kraShader.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class VertexShader {

  public:
    VertexShader() = default;
    virtual
    ~VertexShader() {}

    virtual bool
    compileVertexShader(std::string fileName,
                          const char* entryPoint) = 0;
    virtual bool
    createVertexShader(const Device& pDevice) = 0;
    virtual void
    cleanShader() = 0;
    virtual void
    setVertexShader(Device* pDevice) = 0;

  };
}