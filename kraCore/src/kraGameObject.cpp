#include "kraGameObject.h"

namespace kraEngineSDK {

  void
  GameObject::addComponet(Component* newComponent) {
    //m_componentsVec.push_back(newComponent);
  }

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