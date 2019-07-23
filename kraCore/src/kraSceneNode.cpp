#include "kraSceneNode.h"

namespace kraEngineSDK {
  
  void
  SceneNode::initialize(GameObject* gameObject) {
      
    m_gameObject = gameObject;

  }


  void
  SceneNode::addChild(SceneNode* newChild) {
    m_children.push_back(newChild);
  }

  GameObject*
  SceneNode::getGameObject() {
    return m_gameObject;
  }

  void
  SceneNode::setParent(SceneNode* parent) {
    m_parent = parent;
  }

  SceneNode*
  SceneNode::getParent() {
    return m_parent;
  }

  Vector<SceneNode*>
  SceneNode::getChildren() {
    return m_children;
  }

  /*SceneNode*
  SceneNode::getChild(String name) {

    Vector<SceneNode*>::iterator it = m_children.begin();
    while (it != m_children.end())
    {
      if ((*it)->m_name == name)
      {
        return *it;
      }
    }

    std::cout << "No child with name: " << name << " could be found. \n";
    return nullptr;

  }*/

  SceneNode*
  SceneNode::getChild(uint32 id) {

    Vector<SceneNode*>::iterator it = m_children.begin();
    while(it != m_children.end())
    {
      if ((*it)->m_id == id)
      {
        return *it;
      }
    }

    std::cout << "No child with id: " << id << " could be found. \n";
    return nullptr;

  }

  void
  SceneNode::setID(uint32 id) {
    m_id = id;
  }

  int
  SceneNode::getID() {
    return m_id;
  }

}
