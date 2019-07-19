#pragma once
#include "kraPrerequisitesCore.h"
#include "kraGameObject.h"

namespace kraEngineSDK {

  class KRA_CORE_EXPORT Component
  {
   public:
    Component() = default;
    virtual ~Component() {}
    
    Component*
    getComponent();

    GameObject m_gameObject;
    Transform m_transform;

  };
}