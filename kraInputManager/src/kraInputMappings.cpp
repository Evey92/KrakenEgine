#include "kraPrerequisitesInput.h"
#include "kraInputMappings.h"

namespace kraEngineSDK {

  gainput::DeviceId
  InputMappings::getInputDevice(INPUT_DEVICE::E device) {
    switch (device) 
    {
    case INPUT_DEVICE::kraMOUSE:
      return gainput::;
    case INPUT_DEVICE::kraKEYBOARD:
      return gainput::InputDeviceKeyboard;
    case INPUT_DEVICE::kraGAMEPAD:
      return ;
    case INPUT_DEVICE::kraTOUCH:
      return gainput::InputDevice::DeviceType::DT_TOUCH;
    case INPUT_DEVICE::kraCUSTOM:
      return gainput::InputDevice::DeviceType::DT_CUSTOM;
    
    }
  }
}