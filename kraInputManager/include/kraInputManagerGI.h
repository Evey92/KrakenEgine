#pragma once
#include <gainput/gainput.h>
#include "kraPrerequisitesInput.h"

namespace kraEngineSDK {
  class InputManager {

    void
    setUpInputManager( uint32 width, uint32 height);

    //TODO: Create a proper Mappings file on kraCore to create a specific device
    void
    createDevice(int deviceType);


    gainput::InputManager m_inputManager;
  };
}