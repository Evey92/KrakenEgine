#include "kraSceneGraph.h"

namespace kraEngineSDK {

  void 
  SceneGraph::initialize()
  {
    m_root = new SceneNode();
    m_root->setID(0);
    m_root->initialize(nullptr); /// This is probably really fucking stupid
    m_sceneNodes.push_back(m_root);
  }

  void
  SceneGraph::setNode(SceneNode* newNode) {

    newNode->setID(m_sceneNodes.size());
    newNode->setParent(m_root);
    m_root->addChild(newNode);

    m_sceneNodes.push_back(newNode);
  }

  /*void
  SceneGraph::setNodeAtChildren(SceneNode* newNode, String childName) {
    
    SceneNode* parent = getNode(childName);

    if (!parent)
    {
      std::cout << "No node with name: " << childName << " exists.\n";
      return;
    }
  
    newNode->setID(m_sceneNodes.size());
    newNode->setParent(parent);
    parent->addChild(newNode);
  }*/

  void
  SceneGraph::setNodeAtChildren(SceneNode* newNode, int childID) {
    
    SceneNode* parent = getNode(childID);

    if (!parent)
    {
      std::cout << "No node with ID: " << childID << " exists.\n";
      return;
    }

    newNode->setID(m_sceneNodes.size());
    newNode->setParent(parent);
    parent->addChild(newNode);
  
  }

  /*SceneNode*
  SceneGraph::getNode(String nodeName) {

    Vector<SceneNode*>::iterator it = m_sceneNodes.begin();

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

  }*/

  SceneNode*
  SceneGraph::getNode(int nodeId) {

    Vector<SceneNode*>::iterator it = m_sceneNodes.begin();
    
    while (it != m_sceneNodes.end())
    {
      if ((*it)->getID() == nodeId)
      {
        return *it;
      }
    }

    return nullptr;

  }

  SceneNode*
  SceneGraph::getRootNode()
  {
    return m_root;
  }

  uint32 SceneGraph::getNodesSize()
  {
    return m_sceneNodes.size();
  }

  Vector<SceneNode*> 
  SceneGraph::getSceneNodes()
  {
    return m_sceneNodes;
  }

}