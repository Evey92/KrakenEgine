#include <kraGraphicsAPI.h>

#include "kraD3D11RenderAPIManager.h"
#include "kraD3D11GraphicsAPI.h"

namespace kraEngineSDK {

  GraphicsAPI*
  RenderAPIManagerDX::initializeGraphicsAPI()
  {
    GraphicsAPI::StartUp<GraphicsAPIDX>();
    return GraphicsAPI::instancePtr();
  }

}
