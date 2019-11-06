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
     virtual bool
     createDepthStencilState(const Device& pDevice, bool depthEnable,  DEPTH_WRITE_MASK::E writeMask) = 0;
     virtual void
     setDepthStencilState(const Device& pDevice) = 0;
     virtual void
     cleanDepthStencil() = 0;

  };
}
