#include "kraSceneGraph.h"
#include "kraSceneManager.h"

namespace kraEngineSDK {

  void 
  SceneGraph::initialize()
  {
    m_root = SceneManager::instance().createGameObject("Root");
    m_root->setID(0);
    m_root->initialize(); 
    m_sceneNodes.push_back(m_root);
  }

  void
  SceneGraph::setNode(GameObject* newNode) {

    newNode->setID(m_sceneNodes.size());
    newNode->setParent(m_root);
    m_root->addChild(newNode);

    m_sceneNodes.push_back(newNode);
  }

  void
  SceneGraph::setNodeAtChildren(GameObject* newNode, String childName) {
    
    GameObject* parent = getNode(childName);

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
  SceneGraph::setNodeAtChildren(GameObject* newNode, int childID) {
    
    GameObject* parent = getNode(childID);

    if (!parent)
    {
      std::cout << "No node with ID: " << childID << " exists.\n";
      return;
    }

    newNode->setID(m_sceneNodes.size());
    newNode->setParent(parent);
    parent->addChild(newNode);
  
  }

  GameObject*
  SceneGraph::getNode(String nodeName) {

    Vector<GameObject*>::iterator it = m_sceneNodes.begin();

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

  GameObject*
  SceneGraph::getNode(int nodeId) {

    Vector<GameObject*>::iterator it = m_sceneNodes.begin();
    
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

  GameObject*
  SceneGraph::getRootNode()
  {
    return m_root;
  }

  uint32 SceneGraph::getNodesSize()
  {
    return m_sceneNodes.size();
  }

  Vector<GameObject*>
  SceneGraph::getSceneNodes()
  {
    return m_sceneNodes;
  }

}