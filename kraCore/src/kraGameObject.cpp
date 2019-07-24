#include "kraGameObject.h"

namespace kraEngineSDK {

  

  template<class ComponentType>
  ComponentType&
  GameObject::getComponent()
  {
    for (auto&& component : m_components) {
      if (component->isOfType(ComponentType::Type))
        return *static_cast<ComponentType*>(component.get());
    }

    return nullptr;
  }

}