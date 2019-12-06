#pragma once

#include "kraPrerequisitesCore.h"
#include "kraGameObject.h"

namespace kraEngineSDK {
  class KRA_CORE_EXPORT Light
    : public Component {

    CLASS_DECLARATION(Light)

   public:

    Light(const ShrdPtr<GameObject>& owner)
      : Component(owner) {}

    ~Light() = default;

   private:

     Color m_color;

  };
}
