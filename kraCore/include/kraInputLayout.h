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

    virtual void
    defineInputLayout() = 0;
    virtual void
    defineVertexLayout() = 0;
    virtual void
    defineIndexLayout() = 0;
    virtual void
    defineNormalLayout() = 0;
    virtual void
    defineTexcoordLayout() = 0;
    virtual void
    createInputLayout(Device* pd3dDevice, VertexShader* pVShader) = 0;
    virtual void
    setInputLayout(Device* pDeviceContext) = 0;
    virtual void
    cleanInputLayout() = 0;
  };
}