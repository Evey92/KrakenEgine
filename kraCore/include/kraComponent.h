#pragma once

#include "kraPrerequisitesCore.h"


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
  class Transform;
  
#define CLASS_DECLARATION(classname) 
#define CLASS_DEFINITION(parentclass, childclass) 

  class KRA_CORE_EXPORT Component
  {

   public:
    Component() = default;
    virtual ~Component() = default; 

    bool
    isOfType(const ComponentTypes::E type) const;

   /* GameObject* m_gameObject = nullptr;
    Transform* m_transform = nullptr;*/
    ComponentTypes::E m_type = ComponentTypes::E::DEFAULT;

  };
}