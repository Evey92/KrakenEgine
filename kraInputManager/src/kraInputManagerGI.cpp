#include "kraInputManagerGI.h"
#include "kraInputMappings.h"

namespace kraEngineSDK {
  void
  InputManagerGI::setUpInputManagerGI(uint32 width, uint32 height) {
    gainput::InputManager m_inputManager;
    m_inputManager.SetDisplaySize(width, height);

    //gainput::InputMap map(m_inputManager);

  }

  //void
  //InputManagerGI::mapBoolDevice(uint32 devID, INPUT_DEVICE::E device, uint32 key) {

  //}
  ///*void
  //mapFloatDevice(uint32 devID, INPUT_DEVICE::E device, uint32 key);*/
  //void
  //InputManagerGI::handleMessage(MSG& msg) {

  //}

}