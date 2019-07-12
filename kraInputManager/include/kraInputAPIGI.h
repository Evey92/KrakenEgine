#pragma once
#include <kraInputAPI.h>
#include <kraInputManagerGI.h>
#include "kraPrerequisitesInput.h"

namespace kraEngineSDK {

  class KRA_UTILINPUT_EXPORT InputAPIGI : public InputAPI
  {
  public:

    InputAPIGI() = default;
    ~InputAPIGI() {}

    kraInputManager*
    initializeAPI(uint32 width, uint32 height) override;

    InputManagerGI m_inputManager;

  };
}

MS_ALIGN(16)
extern "C" KRA_UTILINPUT_EXPORT kraEngineSDK::InputAPI*
createInputAPI() {
  return new kraEngineSDK::InputAPIGI();
}
GCC_ALIGN(16)