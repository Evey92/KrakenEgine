#include "kraComponent.h"
#include "kraGameObject.h"

#define CLASS_DECLARATION( classname )  

namespace kraEngineSDK {

  bool 
  Component::isOfType(const ComponentTypes::E type) const
  {
    return m_type == type;
  }
}