#pragma once
#include "kraPrerequisitesCore.h"
#include "kraTexture.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT DepthStencil
  {
   public:

     DepthStencil() = default;
     virtual ~DepthStencil() {};

     virtual void
     createDepthStencil(void* pDevice, int height, int width) = 0;
     
     virtual void
     cleanDepthStencil() = 0;

  };
}
