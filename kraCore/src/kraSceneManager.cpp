#include "kraSceneManager.h"
namespace kraEngineSDK {
  
  Scene* 
  SceneManager::createScene(String name) {
    
    Scene* newScene = new Scene(name);

    newScene->initialize();

    return newScene;
  }

  Scene* 
  SceneManager::createDefaultScene()
  {
    Scene* defaultScene = createScene("defaultScene");
    setActiveScene(defaultScene);
    return defaultScene;
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

}

