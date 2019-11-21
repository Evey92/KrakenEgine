#pragma once
#include "kraComponent.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Collider :
    public Component
  {
    CLASS_DECLARATION(Collider)

   public:
     Collider(const ShrdPtr<GameObject>& owner)
     : Component(owner) {}


  };
}


