#pragma once

#include "kraPrerequisitesCore.h"
#include "componentStuff.h"

namespace kraEngineSDK {                                                  

  namespace ComponentTypes {
    enum E
    {
      DEFAULT = 0,
      TRANSFORM,
      CAMERA,
      COLLIDER,

    };
  }

  class GameObject;

  class KRA_CORE_EXPORT Component
  {

   public:
     Component(GameObject* owner)
     : m_owner(owner) {}

    virtual ~Component() = default; 

    virtual bool isOfType(const std::size_t classType) const;

    static const std::size_t Type;
     GameObject* m_owner = nullptr;

  };
}