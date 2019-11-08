#pragma once
#include "kraPrerequisitesCore.h"
#include "kraModule.h"

namespace kraEngineSDK {

  class Device;

  class RenderPipeline :
    public Module<RenderPipeline> {
  
    public:
      
      RenderPipeline() = default;
      virtual 
      ~RenderPipeline() {}

      virtual void
      initialize(const Device&) = 0;

      virtual void
      Setup() = 0;

      virtual void
      render() = 0;
  };
}