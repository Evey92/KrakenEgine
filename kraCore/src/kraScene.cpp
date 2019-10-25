#include "kraScene.h"
#include "kraGameObject.h"
#include "kraCameraManager.h"
#include "kraCamera.h"
#include "kraSceneManager.h"

namespace kraEngineSDK {


  void
    Scene::initialize()
  {
    m_sceneGraph = new SceneGraph();
    m_sceneGraph->initialize();

    GameObject* newGO = SceneManager::instance().createGameObject("MainCamera");
    newGO->addComponent<Camera>(newGO);
    m_sceneGraph->setNode(newGO);

    CameraManager::instance().registerCamera(&ne.wGO->getComponent<Camera>());
    CameraManager::instance().setActiveCamera(&newGO->getComponent<Camera>());
    GameObject* newEmptyGO = createGameObject();
    m_sceneGraph->setNode(newEmptyGO);

  }

  void
  Scene::addNewNode(GameObject* GO) {
    m_sceneGraph->setNode(GO);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  void
    Scene::addNode(GameObject* node, int id)
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
