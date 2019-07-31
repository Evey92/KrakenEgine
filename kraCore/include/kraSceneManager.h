#pragma once
#include "kraPrerequisitesCore.h"
#include "kraScene.h"

namespace kraEngineSDK {
  
  class KRA_CORE_EXPORT SceneManager
  {
   public:
    SceneManager() = default;
    ~SceneManager() = default;

#pragma region PUBLIC_METHODS
    
    Scene*
    createScene(String name);

    void
    createDefaultScene();

    Scene*
    getActiveScene();

    Scene*
    getSceneByLoadedIndex(int index);

    Scene*
    getSceneByBuildIndex(int index);

    Scene*
    getSceneByName(String name);

    Scene*
    getSceneByPath(String path);

    void
    loadScene(int buildIndex);

    void
    loadScene(String sceneName);

    void
    setActiveScene(Scene* scene);

#pragma endregion PUBLIC_METHODS

   private:
#pragma region PRIVATE_MEMBERS
     
     //Vector<Scene*> m_scenesInBuild;
     Scene* m_activeScene;
     int m_scenesLoadedCount = 0;
     int m_scenesInBuildCount = 0;

#pragma endregion PRIVATE_MEMBERS

  };
}
