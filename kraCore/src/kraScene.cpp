#include "kraScene.h"

namespace kraEngineSDK {


  void
  Scene::initialize()
  {
    m_sceneGraph->initialize();
    
    GameObject* newGO = new GameObject(this, "MainCamera");
    
    //Camera* camGO = new Camera();
    //newGO->addComponent<Camera>(camGO);
    
    SceneNode* newNode = new SceneNode();
    newNode->initialize(newGO);
    m_sceneGraph->setNode(newNode);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  void
  Scene::addNewNode() {
    
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
    SceneNode* newNode = new SceneNode();
    newNode->initialize(nullptr);

    m_sceneGraph->setNode(newNode);
    m_nodes = m_sceneGraph->getNodesSize();
  }

}
