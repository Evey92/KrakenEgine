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
  InputManagerGI::handleMessage(MSG& msg) {
    m_inputManager.HandleMessage(msg);
  }

}