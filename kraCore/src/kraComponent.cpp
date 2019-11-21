#include "kraComponent.h"
#include "kraGameObject.h"

namespace kraEngineSDK {

  bool 
  Component::isOfType(const std::size_t classType) const
  {
    return classType == Type;
  }

  ShrdPtr<GameObject>
  Component::getOwner()
  {
    return m_owner;
  }

  void
  Component::setOwner(const ShrdPtr<GameObject>& newOwner) {
    m_owner = newOwner;
  }
    

  const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

}
