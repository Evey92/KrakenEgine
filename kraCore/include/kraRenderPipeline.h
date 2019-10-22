#pragma once
#include "kraPrerequisitesCore.h"
#include "kraModule.h"

namespace kraEngineSDK {

  class RenderPipeline :
    public Module<RenderPipeline> {
  
    public:
      
      RenderPipeline();
      virtual 
      ~RenderPipeline() {}

      virtual void
      initialize() = 0;

      virtual void
      Setup() = 0;

      virtual void
      render() = 0;
  };
}