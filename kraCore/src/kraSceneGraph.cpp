#include "kraSceneGraph.h"

namespace kraEngineSDK {

  void
  SceneGraph::setNode(SceneNode* newNode) {
    m_sceneNodes.push_back(newNode);
  }

  void
  SceneGraph::setNodeAtChildren(SceneNode* newNode, String childNodeName) {

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