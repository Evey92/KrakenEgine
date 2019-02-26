#pragma once
#include <kraRenderAPIManager.h>

#include "kraPrerequisitesGFX.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT RenderAPIManagerDX : public RenderAPIManager
  {
   public:
    GraphicsAPI*
    initializeGraphicsAPI();

    bool m_APIInitialized;
  };
}

//MS_ALIGN(16)
//extern "C" KRA_UTILGFX_EXPORT kraEngineSDK::GraphicsAPI*
//createGraphicsAPI() {
//  
//  return new kraEngineSDK::GraphicsAPIDX();
//}
//GCC_ALIGN(16)