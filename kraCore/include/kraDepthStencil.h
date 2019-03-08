#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
 
  class DepthStencil
  {
   public:

     DepthStencil() = default;
     virtual ~DepthStencil() {};

     virtual bool
     setDepthStencil(const Device& pDevice, int height, int width) = 0;

     virtual void
     cleanDepthStencil() = 0;

  };
}
