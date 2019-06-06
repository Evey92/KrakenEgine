#pragma once
#include "kraPrerequisitesCore.h"

namespace kraEngineSDK {

  struct Transform
  {
    Vector4 Position;
    Vector4 Rotation;
    Vector4 Scale;
  };

  class KRA_CORE_EXPORT GameObject
  {
   public:
    GameObject();
    ~GameObject() = default;

    void
    addComponet(Type componenType);
    
    bool m_isActive;
    Transform m_transform;
  };
}