#include "kraScene.h"

namespace kraEngineSDK {


  void
  Scene::initialize()
  {
    m_sceneGraph->initialize();
    m_nodes = m_sceneGraph->getNodesSize();
  }

  void
  Scene::addNode(SceneNode* node)
  {
    m_sceneGraph->setNode(node);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  void 
  Scene::addEmptyNode()
  {
    SceneNode* newNode = new SceneNode(m_nodes);
    newNode->initialize(nullptr);

    m_sceneGraph->setNode(newNode);
    m_nodes = m_sceneGraph->getNodesSize();
  }

}
