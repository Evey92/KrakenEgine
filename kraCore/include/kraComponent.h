#pragma once
#include "kraPrerequisitesCore.h"


namespace kraEngineSDK {

  namespace ComponentType {
    enum E
    {
      TRANSFORM = 0,
      CAMERA,
      COLLIDER,

    };
  }

  class GameObject;
  class Transform;
  
  class KRA_CORE_EXPORT Component
  {
   public:
    Component() = default;
    virtual ~Component() = default;
    
    Component*
    getComponent(ComponentType.E type);

    GameObject* m_gameObject;
    Transform* m_transform;

  };
}