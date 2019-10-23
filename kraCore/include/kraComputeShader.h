#pragma once
#include "kraPrerequisitesCore.h"
#include "kraShader.h"
#include "kraDevice.h"

namespace kraEngineSDK {
  class ComputeShader {

   public:

    ComputeShader() = default;
    
    virtual
    ~ComputeShader() {}

    virtual bool
    compileComputeShader(const WString fileName,
                        String entryPoint) = 0;

    virtual bool
    createComputeShader(const Device& pDevice) = 0;
    
    virtual void
    cleanShader() = 0;
    
    virtual void
    setComputeShader(const Device& pDevice) = 0;

  };
}