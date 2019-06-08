#include "kraSceneGraph.h"

namespace kraEngineSDK {

  void
  SceneGraph::setNode(SceneNode* newNode) {

    newNode->setID(m_sceneNodes.size());
    m_sceneNodes.push_back(newNode);
  }

  void
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
  }

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

  SceneNode*
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

  }

  SceneNode*
  SceneGraph::getNode(int nodeId) {

    Vector<SceneNode*>::iterator it = m_sceneNodes.begin();
    
    while (it != m_sceneNodes.end())
    {
      if ((*it)->getID() == nodeId)
      {
        return *it;
      }
      else
      {
        if ((*it)->getChild(nodeId) != nullptr)
        {
          return *it;

        }
      }
    }

  }

}