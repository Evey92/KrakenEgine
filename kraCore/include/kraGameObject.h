#pragma once
#include "kraPrerequisitesCore.h"
#include "kraComponent.h"

namespace kraEngineSDK {

  struct Transform
  {
    Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 Scale = Vector3(0.0f, 0.0f, 0.0f);
  };

  class KRA_CORE_EXPORT GameObject
  {
   public:
    GameObject();
    ~GameObject() = default;

    void
    addComponet(Component* newComponent);
    
    Vector<Component*> m_componentsVec;
    Transform m_transform;
    Scene* m_scene;
    String m_name = "GameObject";
    bool m_isActive = true;

  };
}
