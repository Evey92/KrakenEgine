#include "kraInputManagerGI.h"
#include "kraInputMappings.h"

enum buttons
{
  Dkey,
  Akey,
};

namespace kraEngineSDK {
  void
   InputManagerGI::managerUpdate() {
    m_inputManager.Update();
  }
  void
  InputManagerGI::setUpInputManagerGI(uint32 width, uint32 height) {
    m_inputManager.SetDisplaySize(width, height);
  }

  void
  InputManagerGI::setInputMap(){
    m_map = new gainput::InputMap(m_inputManager);
  }

  uint32
  InputManagerGI::createMouseDevice() {
    return m_inputManager.CreateDevice<gainput::InputDeviceMouse>();
  }
  uint32
  InputManagerGI::createKeyboardDevice() {
    return m_inputManager.CreateDevice<gainput::InputDeviceKeyboard>();

  }
  uint32
  InputManagerGI::createGamepadDevice() {
    return m_inputManager.CreateDevice<gainput::InputDevicePad>();

  }

  void
  InputManagerGI::mapBoolDevice(uint32 userButton, uint32 devID, uint32 key) {
    gainput::DeviceId m_devID = static_cast<gainput::DeviceId>(devID);
    gainput::DeviceButtonId m_key = static_cast<gainput::DeviceButtonId>(key);
    

    m_map->MapBool(userButton, m_devID, key);

  }

  bool
  InputManagerGI::mapFloatDevice(uint32 userButton, uint32 devID, uint32 key) {

    gainput::UserButtonId m_Btn = static_cast<gainput::UserButtonId>(userButton);
    gainput::DeviceId m_devID = static_cast<gainput::DeviceId>(devID);
    gainput::DeviceButtonId m_key = static_cast<gainput::DeviceButtonId>(key);
  
    m_map->MapFloat(m_Btn, m_devID, m_key);
    return true;
  }

  void
  InputManagerGI::handleMessage(void* msg) {
    MSG* m_msg = static_cast<MSG*>(msg);

    m_inputManager.HandleMessage(*m_msg);
  }

  bool
  InputManagerGI::boolWasDown(uint32 userDevice) {
    
    if(!m_map->GetBoolWasDown(userDevice)) {
      return false;
    }

    return true;
  }
  bool
  InputManagerGI::floatDelta(uint32 userDevice) {
    if (!m_map->GetFloatDelta(userDevice)) {
      return false;
    }
    return true;
  }

}