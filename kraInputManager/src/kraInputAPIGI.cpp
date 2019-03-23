#include "kraInputAPIGI.h"

namespace kraEngineSDK {

 InputManager*
 InputAPIGI::initializeAPI(uint32 width, uint32 height) {

   m_inputManager.setUpInputManagerGI(width, height);

   return &m_inputManager;
 }
}

