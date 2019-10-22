#include "kraPBRenderPipelineManager.h"
namespace kraEngineSDK{

  RenderPipeline *
  PBRenderManager::initializeRenderPipeline()
  {
    return RenderPipeline::instancePtr();
  }
}
