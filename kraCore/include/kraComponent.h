#pragma once

#include "kraPrerequisitesCore.h"
#include "componentStuff.h"

namespace kraEngineSDK {                                                  

  namespace GOComponentTypes {
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
     Component(ShrdPtr<GameObject> owner)
     : m_owner(owner) {}

    virtual ~Component() = default; 

    virtual bool
    isOfType(const std::size_t classType) const;

    ShrdPtr<GameObject>
    getOwner();

    void
    setOwner(const ShrdPtr<GameObject>& newOwner);

    static const std::size_t Type;
   
   protected:
     ShrdPtr<GameObject> m_owner = nullptr;

  };
}