#include "kraGameObject.h"

namespace kraEngineSDK {
  
  void 
  GameObject::initialize()
  {
    addComponent<Transform>(this);
  }

  void 
  GameObject::addChild(GameObject* newChild)
  {
    m_children.push_back(newChild);
  }


  void 
  GameObject::setParent(GameObject* parent)
  {
    m_parent = parent;
  }

  GameObject* 
  GameObject::getParent()
  {
    return m_parent;
  }

  Vector<GameObject*> 
  GameObject::getChildren()
  {
    return m_children;
  }

  GameObject* 
  GameObject::getChild(String name)
  {
    for (auto* child : m_children)
    {
      if (child->m_name == name)
      {
        return child;
      }
    }

    return nullptr;
  }

  GameObject* 
  GameObject::getChild(uint32 id)
  {
    for (auto* child : m_children)
    {
      if (child->m_id == id)
      {
        return child;
      }
    }

    return nullptr;
  }

  void 
  GameObject::setID(uint32 id)
  {
    m_id = id;
  }

  uint32 
  GameObject::getID()
  {
    return m_id;
  }

  String 
  GameObject::getName()
  {
    return m_name;
  }

}