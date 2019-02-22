#pragma once
#include <kraRenderAPIManager.h>

namespace kraEngineSDK {
  class RenderAPIManagerDX : public RenderAPIManager
  {
    
    GraphicsAPI*
    initializeGraphicsAPI();

    bool m_APIInitialized;
  };
}