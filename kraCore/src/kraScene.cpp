#include "kraScene.h"
#include "kraGameObject.h"
#include "kraCameraManager.h"
#include "kraCamera.h"
#include "kraSceneManager.h"

namespace kraEngineSDK {


  void
    Scene::initialize()
  {
    m_sceneGraph = make_shared<SceneGraph>();
    m_sceneGraph->initialize();

    ShrdPtr<GameObject> newGO = SceneManager::instance().createGameObject("MainCamera");
    newGO->addComponent<Camera>(newGO);
    m_sceneGraph->setNode(newGO);

    CameraManager::instance().registerCamera(&newGO->getComponent<Camera>());
    CameraManager::instance().setActiveCamera(&newGO->getComponent<Camera>());

  }

  void
  Scene::addNewNode(const ShrdPtr<GameObject>& GO) {
    m_sceneGraph->setNode(GO);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  void
  Scene::addNode(const ShrdPtr<GameObject>& node, int id)
  {
    m_sceneGraph->setNodeAtChildren(node, id);
    m_nodes = m_sceneGraph->getNodesSize();
  }

  /*ShrdPtr<GameObject>
  Scene::createGameObject()
  {
    SceneNode* newNode = new SceneNode();
    ShrdPtr<GameObject> newGO = make_shared<GameObject>(this);
    newGO->initialize(newGO, );
    return newGO;
  }

  ShrdPtr<GameObject>
  Scene::createGameObject(String name)
  {
    SceneNode* newNode = new SceneNode();
    ShrdPtr<GameObject> newGO = make_shared<GameObject>(this, name);
    newGO->initialize(newGO);
    return newGO;
  }*/


}
