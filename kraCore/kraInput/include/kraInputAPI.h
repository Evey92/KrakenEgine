#pragma once
#include "kraPrerequisitesCore.h"
#include "kraInput/include/kraInputManager.h"
namespace kraEngineSDK {

  class InputAPI
  {
  public:

    InputAPI() = default;
    virtual
    ~InputAPI() {}

    virtual InputManager*
    initializeAPI(uint32 width, uint32 height) = 0;


  };
}