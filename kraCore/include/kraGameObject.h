#pragma once
#include "kraPrerequisitesCore.h"
#include "kraComponent.h"

namespace kraEngineSDK {

  struct Transform
  {
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scale;
  };

  class KRA_CORE_EXPORT GameObject
  {
   public:
    GameObject();
    ~GameObject() = default;

    void
    addComponet(Component* newComponent);
    
   private:
    
    bool m_isActive;
    Transform m_transform;
    Vector<Component*> m_componentsVec;

  };
}
