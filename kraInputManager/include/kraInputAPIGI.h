#pragma once
#include <kraInput/include/kraInputAPI.h>

#include "kraPrerequisitesInput.h"
#include "kraInputManagerGI.h"

namespace kraEngineSDK {

  class KRA_UTILINPUT_EXPORT InputAPIGI : public InputAPI
  {
  public:

    InputAPIGI() = default;
    ~InputAPIGI() {}

    InputManager*
    initializeAPI(uint32 width, uint32 height);

    InputManagerGI m_inputManager;

  };
}

MS_ALIGN(16)
extern "C" KRA_UTILINPUT_EXPORT kraEngineSDK::InputAPI*
createInputAPI() {
  return new kraEngineSDK::InputAPIGI();
}
GCC_ALIGN(16)