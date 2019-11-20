#include "kraSceneManager.h"
namespace kraEngineSDK {
  
  Scene* 
  SceneManager::createScene(String name) {
    
    Scene* newScene = new Scene(name);

    newScene->initialize();

    return newScene;
  }

  void 
  SceneManager::createEmptyScene()
  {
	
	  String scenename = "Scene " + std::to_string( m_loadedScenes.size());
    
	Scene* defaultScene = createScene(scenename);
    m_loadedScenes.push_back(defaultScene);
    setActiveScene(defaultScene);
    defaultScene->initialize();
  }

  GameObject*
  SceneManager::createGameObject()
  {

    GameObject* newGO = new GameObject(getActiveScene());
    newGO->initialize();
    return newGO;
  }

  GameObject*
  SceneManager::createGameObject(String name)
  {
    GameObject* newGO = new GameObject(m_activeScene, name);
    newGO->initialize();
    return newGO;
  }

  Scene*
  SceneManager::getActiveScene()
  {
    return m_activeScene;
  }

  Scene* 
  SceneManager::getSceneByLoadedIndex(int index)
  {
    Scene* loadedScene = new Scene("place holder");

    return loadedScene;
  }

  Scene* 
  SceneManager::getSceneByBuildIndex(int index)
  {
    Scene* loadedScene = new Scene("place holder");

    return loadedScene;
  }

  Scene* 
  SceneManager::getSceneByName(String name)
  {
    Scene* loadedScene = new Scene("place holder");

    return loadedScene;
  }

  Scene* 
  SceneManager::getSceneByPath(String path)
  {
    Scene* loadedScene = new Scene("place holder");

    return loadedScene;
  }

  void 
  SceneManager::loadScene(int buildIndex)
  {

  }

  void 
  SceneManager::loadScene(String sceneName)
  {
    //Here the resource manager should look for a scene
  }

  void 
  SceneManager::setActiveScene(Scene* scene)
  {
    m_activeScene = scene;
  }

  void SceneManager::onStartUp()
  {
    createEmptyScene();
  }

  void SceneManager::onShutdown()
  {
    
  }

}

