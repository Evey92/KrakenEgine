#include "kraScene.h"
#include "kraGameObject.h"
#include "kraCamera.h"

namespace kraEngineSDK {


  void
    Scene::initialize()
  {
    m_sceneGraph = new SceneGraph();
    m_sceneGraph->initialize();

    GameObject* newGO = createGameObject("MainCamera");
    newGO->addComponent<Camera>(newGO);
    
    SceneNode* newNode = new SceneNode();
    newNode->initialize(newGO);

    m_sceneGraph->setNode(newNode);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  void
    Scene::addNewNode() {

  }



  void
    Scene::addNode(SceneNode* node, int id)
  {
    m_sceneGraph->setNodeAtChildren(node, id);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  GameObject*
  Scene::createGameObject()
  {
    SceneNode* newNode = new SceneNode();
    GameObject* newGO = new GameObject(this);
    newGO->initialize();
    return newGO;
  }

  GameObject*
  Scene::createGameObject(String name)
  {
    SceneNode* newNode = new SceneNode();
    GameObject* newGO = new GameObject(this, name);
    newGO->initialize();
    return newGO;
  }

}
