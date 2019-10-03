#pragma once
#include "kraPrerequisitesCore.h"
#include <kraModule.h>
#include "kraScene.h"

namespace kraEngineSDK {
  
  class KRA_CORE_EXPORT SceneManager :
    public Module<SceneManager>
  {
   public:
    SceneManager() = default;
    ~SceneManager() = default;

#pragma region PUBLIC_METHODS
    
    Scene*
    createScene(String name);

    void
    createEmptyScene();

    GameObject*
    createGameobject();

    GameObject*
    createGameObject(String name);

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
     Scene* m_activeScene = nullptr;
     int m_scenesLoadedCount = 0;
     int m_scenesInBuildCount = 0;
     Vector<Scene*> m_loadedScenes;
#pragma endregion PRIVATE_MEMBERS

  protected:
    void onStartUp() override;


    void onShutdown() override;

  };
}
