#pragma once
#include <kraRenderAPIManager.h>
#include <kraGraphicsAPI.h>

#include "kraPrerequisitesGFX.h"
#include "kraD3D11GraphicsAPI.h"

namespace kraEngineSDK {
  class KRA_UTILGFX_EXPORT RenderAPIManagerDX : public RenderAPIManager
  {
   public:

     RenderAPIManagerDX() = default;
     ~RenderAPIManagerDX() {};

    GraphicsAPI*
    initializeGraphicsAPI();

    bool m_APIInitialized;
  };

  /*GraphicsAPI*
    extern "C" KRA_CORE_EXPORT initializeGraphicsAPI() {

    return new GraphicsAPIDX();
  }*/

}

MS_ALIGN(16)
extern "C" KRA_UTILGFX_EXPORT kraEngineSDK::GraphicsAPI*
createGraphicsAPI() {
 
  kraEngineSDK::GraphicsAPI::StartUp<kraEngineSDK::GraphicsAPIDX>();
  return kraEngineSDK::GraphicsAPI::instancePtr();
}
GCC_ALIGN(16)