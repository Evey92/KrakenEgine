#pragma once
#include "kraPrerequisitesCore.h"
#include "kraTransform.h"
#include "kraComponent.h"

namespace kraEngineSDK {

  class Scene;

  class KRA_CORE_EXPORT GameObject
  {
   public:
    GameObject() = default;
    ~GameObject() = default;
    GameObject(const GameObject&) = delete;
    GameObject& operator =(const GameObject&) = delete;

    void
    addComponet(Component* newComponent);
    
    template<class ComponentType>
    ComponentType& 
    getComponent();

    Transform m_transform;
    Scene* m_scene = nullptr;
    String m_name = "GameObject";
    Vector<std::unique_ptr<Component>> m_components;
    bool m_isActive = true;

  };

  

}
