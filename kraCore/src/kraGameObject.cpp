#include "kraGameObject.h"

namespace kraEngineSDK {
  
  void GameObject::initialize()
  {
    addComponent<Transform>(this);
  }

}