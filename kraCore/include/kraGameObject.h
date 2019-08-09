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
     : m_scene(scene), m_name(name), m_transform(this) {}

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

      return *std::unique_ptr<ComponentType>(nullptr);
    }

    Transform m_transform;
    GameObject* m_parent = nullptr;
    Vector<GameObject*> m_children;
    Vector<std::unique_ptr<Component>> m_components;
    Scene* m_scene;
    uint32 m_id = 0;
    String m_name;
    bool m_isActive = true;

  };

  
  

}
