#pragma once
#include "kraPrerequisitesCore.h"
#include "kraInputManager.h"

namespace kraEngineSDK {

  class InputAPI
  {
  public:

    InputAPI() = default;
    virtual
    ~InputAPI() {}

    virtual kraInputManager*
    initializeAPI(uint32 width, uint32 height) = 0;


  };
}