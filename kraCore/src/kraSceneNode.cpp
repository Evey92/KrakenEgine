#include "kraSceneNode.h"

namespace kraEngineSDK {
  
  SceneNode::SceneNode() {
      
    m_gameObject = new GameObject();

  }


  void
  SceneNode::addChild(SceneNode* newChild) {
    m_children.push_back(newChild);
  }

  GameObject*
  SceneNode::getGameObject() {
    return m_gameObject;
  }

  SceneNode*
  SceneNode::getPatrent(SceneNode* newNode) {
    return m_parent;
  }

  Vector<SceneNode*>
  SceneNode::getChildren() {
    return m_children;
  }

  SceneNode*
  SceneNode::getChild(int id) {

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

  int
  SceneNode::getID() {
    return m_id;
  }

}
