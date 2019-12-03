#include "kraGameObject.h"

namespace kraEngineSDK {
  
  void 
  GameObject::initialize(const ShrdPtr<GameObject>& thisGO, Scene* scene, String name)
  {
    m_name = name;
    m_scene = scene;
    m_transform = &this->getComponent<Transform>();
  }

  void 
  GameObject::addChild(const ShrdPtr<GameObject>& newChild)
  {
    newChild->setParent(shared_from_this());
    m_children.push_back(newChild);
  }


  void 
  GameObject::setParent(const ShrdPtr<GameObject>& parent)
  {
    m_parent = parent;
  }

  ShrdPtr<GameObject>
  GameObject::getParent()
  {
    return m_parent;
  }

  Vector<ShrdPtr<GameObject>>
  GameObject::getChildren()
  {
    return m_children;
  }

  ShrdPtr<GameObject>
  GameObject::getChild(String name)
  {
    for (auto& child : m_children)
    {
      if (child->m_name == name)
      {
        return child;
      }
    }

    return nullptr;
  }

  ShrdPtr<GameObject>
  GameObject::getChild(uint32 id)
  {
    for (auto& child : m_children)
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

  Matrix4
  GameObject::getWorldMatrix()
  {
    if (!m_parent->m_isRoot)
    {
      return m_transform->getTransformMatrix() * m_parent->getWorldMatrix();
    }

    return m_transform->getTransformMatrix();

  }

}