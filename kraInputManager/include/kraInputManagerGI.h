#pragma once
#include <kraCommonTypes.h>
#include <gainput/gainput.h>
#include <kraInputManager.h>

#include "kraPrerequisitesInput.h"
#include "kraInputMapGI.h"

namespace kraEngineSDK {
  class KRA_UTILINPUT_EXPORT InputManagerGI : public kraInputManager
  {

   public:

     InputManagerGI() = default;
     ~InputManagerGI() {};
     
     void
     managerUpdate();
     void
     setUpInputManagerGI(uint32 width, uint32 height);
     void
     setInputMap();
     uint32
     createMouseDevice();
     uint32
     createKeyboardDevice();
     uint32
     createGamepadDevice();
     bool
     boolWasDown(uint32 userDevice);
     bool
     floatDelta(uint32 userDevice);
    //TODO: Create a proper Mappings file on kraCore to create a specific device
    void
    mapBoolDevice(uint32 userButton, uint32 devID, uint32 key);
    bool
    mapFloatDevice(uint32 userButton, uint32 devID, uint32 key);
    void
    handleMessage(void* msg);
    

    gainput::InputManager m_inputManager;

    gainput::InputMap* m_map;
  };
}