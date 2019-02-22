#pragma once
#include "kraPrerequisitesCore.h"
#include "kraGraphicsAPI.h"

namespace kraEngineSDK {

  class RenderAPIManager {

   public:

    RenderAPIManager() = default;
    RenderAPIManager() {}

    virtual GraphicsAPI*
    initializeGraphicsAPI() = 0;


  };

}