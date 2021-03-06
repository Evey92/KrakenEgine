#pragma once
#include "kraPrerequisitesCore.h"
#include "kraCommonTypes.h"

namespace kraEngineSDK {

  //class InputManagerGI;

  class kraInputManager 
  {

   public:

     kraInputManager() = default;
     ~kraInputManager() {};
     
     virtual void
     managerUpdate() = 0;
     virtual void
     setUpInputManagerGI(uint32 width, uint32 height) = 0;
     virtual void
     setInputMap() = 0;
     virtual uint32
     createMouseDevice() = 0;
     virtual uint32
     createKeyboardDevice() = 0;
     virtual uint32
     createGamepadDevice() = 0;
     virtual bool
     boolWasDown(uint32 userDevice) = 0;
     virtual bool
     floatDelta(uint32 userDevice) = 0;
    //TODO: Create a proper Mappings file on kraCore to create a specific device
    virtual void
    mapBoolDevice(uint32 userButton, uint32 devID, uint32 key) = 0;
    virtual bool
    mapFloatDevice(uint32 userButton, uint32 devID, uint32 key) = 0;
    virtual void
    handleMessage(void* msg) = 0;
  };

}