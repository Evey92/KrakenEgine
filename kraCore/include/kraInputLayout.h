#pragma once
#include "kraPrerequisitesCore.h"
#include "kraVertexShader.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT InputLayout
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
    createInputLayout(void* pd3dDevice, void* pVShader) = 0;
    virtual void
      setInputLayout(void* pDeviceContext) = 0;
    virtual void
      cleanInputLayout() = 0;
  };
}