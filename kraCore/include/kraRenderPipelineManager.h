#pragma once
#include "kraPrerequisitesCore.h"
#include "kraRenderPipeline.h"

namespace kraEngineSDK {

  class RenderPipelineManager {

  public:

    RenderPipelineManager() = default;
    ~RenderPipelineManager() {}

    virtual RenderPipeline*
    initializeRenderPipeline() = 0;


  };

}
