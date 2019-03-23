#pragma once
#include <kraCommonTypes.h>


namespace kraEngineSDK {
  class InputMappingsGI
  {
   public:
    
     static gainput::InputDevice::DeviceType
    getInputDevice(INPUT_DEVICE::E device);

  };
}