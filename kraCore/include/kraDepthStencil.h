#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  class Device;

  class DepthStencil
  {
   public:

     DepthStencil() = default;
     virtual ~DepthStencil() {};

     virtual bool
     setDepthStencil(const Device& pDevice, uint32 height, uint32 width) = 0;

     virtual void
     cleanDepthStencil() = 0;

  };
}
