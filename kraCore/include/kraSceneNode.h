#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT SceneNode
  {
   public:
     SceneNode() = default;
     ~SceneNode() { Destroy(); }

     void 
     Destroy();

  };
}