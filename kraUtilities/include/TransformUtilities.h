#pragma once
#include "kraPrerequisitesUtil.h"
#include "kraMatrix4.h"

namespace kraEngineSDK {
  namespace Utility {
    
    //Crude implementation of euler angles for rotation
    static
    Matrix4
    eulerAngleXY(float angleX, float angleY);
    
  }
}