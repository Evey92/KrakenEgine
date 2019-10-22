#pragma once
#include <kraRenderPipelineManager.h>
#include <kraRenderPipeline.h>

#include "kraPBRPipelineRenderer.h"

namespace kraEngineSDK {
  class KRA_RENDERER_EXPORT PBRenderManager :
    public RenderPipelineManager {
      
   public:

     PBRenderManager();
     ~PBRenderManager();

     RenderPipeline*
     initializeRenderPipeline() override;

  };
}

MS_ALIGN(16)
extern "C" KRA_RENDERER_EXPORT kraEngineSDK::RenderPipeline*
createRenderPipeline() {

  kraEngineSDK::RenderPipeline::StartUp<kraEngineSDK::DeferredPBRenderer>();
  return kraEngineSDK::RenderPipeline::instancePtr();
}
GCC_ALIGN(16)