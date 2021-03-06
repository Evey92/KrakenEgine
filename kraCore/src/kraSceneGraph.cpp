#include "kraSceneGraph.h"
#include "kraSceneManager.h"

namespace kraEngineSDK {

  void 
  SceneGraph::initialize()
  {
    m_root = SceneManager::instance().createGameObject("Root");
    m_root->m_isRoot = true;
    m_root->setID(0);
    m_sceneNodes.push_back(m_root);
  }

  void
  SceneGraph::setNode(const ShrdPtr<GameObject>& newNode) {

    newNode->setID(m_sceneNodes.size());
    newNode->setParent(m_root);
    m_root->addChild(newNode);

    m_sceneNodes.push_back(newNode);
  }

  void
  SceneGraph::setNodeAtChildren(const ShrdPtr<GameObject>& newNode, String childName) {
    
    ShrdPtr<GameObject> parent = getNode(childName);

    if (!parent)
    {
      std::cout << "No node with name: " << childName << " exists.\n";
      return;
    }
  
    newNode->setID(m_sceneNodes.size());
    newNode->setParent(parent);
    parent->addChild(newNode);
  }

  void
  SceneGraph::setNodeAtChildren(const ShrdPtr<GameObject>& newNode, int childID) {
    
    ShrdPtr<GameObject> parent = getNode(childID);

    if (!parent)
    {
      std::cout << "No node with ID: " << childID << " exists.\n";
      return;
    }

    newNode->setID(m_sceneNodes.size());
    newNode->setParent(parent);
    parent->addChild(newNode);
  
  }

  ShrdPtr<GameObject>
  SceneGraph::getNode(String nodeName) {

    Vector<ShrdPtr<GameObject>>::iterator it = m_sceneNodes.begin();

    while (it != m_sceneNodes.end())
    {
      if ((*it)->getName() == nodeName)
      {
        return *it;
      }
      else
      {
        if ((*it)->getChild(nodeName) != nullptr)
        {
          return *it;

        }
      }
    }

  }

  ShrdPtr<GameObject>
  SceneGraph::getNode(int nodeId) {

    Vector<ShrdPtr<GameObject>>::iterator it = m_sceneNodes.begin();
    
    while (it != m_sceneNodes.end())
    {
      if ((*it)->getID() == nodeId)
      {
        return *it;
      }
      ++it;
    }

    return nullptr;

  }

  ShrdPtr<GameObject>
  SceneGraph::getRootNode()
  {
    return m_root;
  }

  uint32 SceneGraph::getNodesSize()
  {
    return m_sceneNodes.size();
  }

  Vector<ShrdPtr<GameObject>>
  SceneGraph::getSceneNodes()
  {
    return m_sceneNodes;
  }

  void 
  SceneGraph::deleteNode(int nodeId)
  {
    ShrdPtr<GameObject> nodeTodel = getNode(nodeId);
    //ShrdPtr<GameObject> nodeParent = nodeTodel->getParent();

    std::cout << "Deleting game object\n";

    /*for (auto& child : nodeTodel->getChildren()) {
      deleteNode(child->getID());
    }*/
  }

  void 
  SceneGraph::deleteNode(String nodeName)
  {
    ShrdPtr<GameObject> nodeTodel = getNode(nodeName);
    ShrdPtr<GameObject> nodeParent = nodeTodel->getParent();

    for (auto& child : nodeTodel->getChildren()) {
      deleteNode(child->getID());
    }

  }

}