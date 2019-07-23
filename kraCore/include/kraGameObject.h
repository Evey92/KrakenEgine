#pragma once
#include "kraPrerequisitesCore.h"
#include "kraTransform.h"
#include "kraComponent.h"

namespace kraEngineSDK {

  class Scene;

  class KRA_CORE_EXPORT GameObject
  {
   public:
    GameObject();
    ~GameObject() = default;

    void
    addComponet(Component* newComponent);
    
    Vector<std::unique_ptr<Component>> m_componentsVec;
    Transform m_transform;
    Scene* m_scene;
    String m_name = "GameObject";
    bool m_isActive = true;

  };
}
