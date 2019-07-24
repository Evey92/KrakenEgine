#pragma once

#include "kraPrerequisitesCore.h"

#define CLASS_DECLARATION( classname )                                                      \
public:                                                                                     \
    static const ComponentTypes::E m_type;                                                  \
    virtual bool isOfType(const ComponentTypes::E type) const override;                     \            

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
  
#define CLASS_DEFINITION(parentclass, childclass) 

  class KRA_CORE_EXPORT Component
  {

   public:
    Component() = default;
    virtual ~Component() = default; 

    bool
    isOfType(const ComponentTypes::E type) const;

   protected:
    ComponentTypes::E m_type = ComponentTypes::E::DEFAULT;
    GameObject* m_owner;

  };
}