#include "kraInputManagerGI.h"
#include "kraInputMappings.h"

namespace kraEngineSDK {
  void
   InputManagerGI::managerUpdate() {
    m_inputManager.Update();
  }
  void
  InputManagerGI::setUpInputManagerGI(uint32 width, uint32 height) {
    
    m_inputManager.SetDisplaySize(width, height);
    
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
    //gainput::InputMap map(m_inputManager);

    m_map.MapBool(userButton, devID, key);

  }

  void
  InputManagerGI::mapFloatDevice(uint32 userButton, uint32 devID, uint32 key) {
    //gainput::InputMap map(m_inputManager);
    m_map.MapFloat(userButton, devID, key);
  }

  void
  InputManagerGI::handleMessage(void* msg) {
    MSG* m_msg = static_cast<MSG*>(msg);

    m_inputManager.HandleMessage(*m_msg);
  }

  bool
  InputManagerGI::boolWasDown(uint32 userDevice) {
    
    if(!m_map.GetBoolWasDown(userDevice)) {
      return false;
    }

    return true;
  }
  bool
  InputManagerGI::floatDelta(uint32 userDevice) {
    if (!m_map.GetFloatDelta(userDevice)) {
      return false;
    }
    return true;
  }

}