#pragma once
#include "kraPrerequisitesCore.h"
#include "kraTransform.h"
#include "kraComponent.h"

namespace kraEngineSDK {

  class Scene;

  class KRA_CORE_EXPORT GameObject
  {
   public:
     GameObject(Scene* scene, String name = "GameObject")
     : m_scene(scene), m_name(name) {}

    ~GameObject() = default;

    GameObject(const GameObject&) = delete;
    GameObject& operator =(const GameObject&) = delete;

    void
    initialize();

    template<class ComponentType, typename... Args>
    void addComponent(Args&& ... params) {
      m_components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(params)...));
    }
    
    template<class ComponentType>
    ComponentType&
    getComponent() {
      for (auto&& component : m_components) {
        if (component->isOfType(ComponentType::Type))
          return *static_cast<ComponentType*>(component.get());
      }

      return nullptr;
    }

    //Transform m_transform;
    Scene* m_scene;
    String m_name;
    Vector<std::unique_ptr<Component>> m_components;
    bool m_isActive = true;

  };

  
  

}
