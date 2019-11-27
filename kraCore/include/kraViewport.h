#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  class Device;
  class Viewport
  {
   public:
    Viewport() = default;
    
    virtual
    ~Viewport() {}

    virtual void
    createViewport(uint32 width, uint32 height, float TopLeftX, float TopLeftY) = 0;

    virtual void
    setViewport(const Device& pDeviceContext) = 0;
  };
}