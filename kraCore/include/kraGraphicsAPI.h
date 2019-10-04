#pragma once
#include "kraPrerequisitesCore.h"
#include "kraModule.h"
#include "kraDevice.h"

namespace kraEngineSDK {

  class GraphicsAPI : 
  public Module<GraphicsAPI> {
   
   public:

    GraphicsAPI() = default;
    virtual
     ~GraphicsAPI() {}

    virtual bool
    initializeAPI(void* g_hWnd) = 0;

    virtual void
    Render() = 0;

    virtual Device*
    getDevice() = 0;

    virtual void
    Cleanup() = 0;


  

  };
}