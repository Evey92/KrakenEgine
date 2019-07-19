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
  }

  Scene* 
  SceneManager::getActiveScene()
  {

  }

  Scene* 
  SceneManager::getSceneByLoadedIndex(int index)
  {

  }

  Scene* 
  SceneManager::getSceneByBuildIndex(int index)
  {

  }

  Scene* 
  SceneManager::getSceneByName(String name)
  {

  }

  Scene* 
  SceneManager::getSceneByPath(String path)
  {

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

