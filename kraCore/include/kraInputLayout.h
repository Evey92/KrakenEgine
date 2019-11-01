#pragma once
#include "kraPrerequisitesCore.h"


namespace kraEngineSDK {

  class VertexShader;
  class Device;
  class InputLayout
  {
   public:

    InputLayout() = default;
    virtual 
      ~InputLayout() {}

    
    virtual bool
    createInputLayout(const Device& pd3dDevice, const VertexShader& pVShader) = 0;
    
    virtual void
    setInputLayout(const Device& pDevice) = 0;
    
    virtual void
    setNullInputLayout(const Device& pDevice) = 0;
    
    virtual void
    cleanInputLayout() = 0;
  };
}