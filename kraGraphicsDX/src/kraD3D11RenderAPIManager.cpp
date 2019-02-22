#include <kraGraphicsAPI.h>

#include "kraD3D11RenderAPIManager.h"
#include "kraD3D11GraphicsAPI.h"

namespace kraEngineSDK {

  GraphicsAPI* 
  RenderAPIManagerDX::initializeGraphicsAPI() {
    
    if (!m_APIInitialized) {
      m_APIInitialized = true;
      return new GraphicsAPIDX();
    }

    return nullptr;
  }

}