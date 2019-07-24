#include "kraComponent.h"
#include "kraGameObject.h"

#define CLASS_DECLARATION( classname )  

namespace kraEngineSDK {

  bool 
  Component::isOfType(const std::size_t classType) const
  {
    return classType == Type;
  }

}
