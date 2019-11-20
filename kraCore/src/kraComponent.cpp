#include "kraComponent.h"
#include "kraGameObject.h"

namespace kraEngineSDK {

  bool 
  Component::isOfType(const std::size_t classType) const
  {
    return classType == Type;
  }

  GameObject*
  Component::getOwner()
  {
    return m_owner;
  }

  void
  Component::setOwner(GameObject* newOwner) {
    m_owner = newOwner;
  }
    

  const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

}
